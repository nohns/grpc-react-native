//
//  grpc-rn-client.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#include "grpc-rn-client.h"
#include "grpc-rn-exceptions.h"
#include <time.h>

namespace GrpcRN {

static void* tag(int i) { return (void*)(intptr_t)i; }

Client::Client(std::shared_ptr<grpc::ChannelInterface> channel) {
    generic_stub_.reset(new grpc::GenericStub(channel));
    channel_ = channel;
}

grpc::Slice Client::unaryCall(grpc::Status& status, std::string method_name, uint8_t *msg_buf, size_t msg_buf_size) {
    
    void* got_tag;
    bool ok;
    
    grpc::ClientContext cli_ctx;
    auto timeout = std::chrono::system_clock::now() +
        std::chrono::milliseconds(5000);
    cli_ctx.set_deadline(timeout);
    
    std::unique_ptr<grpc::GenericClientAsyncReaderWriter> call = generic_stub_->Call(&cli_ctx, method_name, &cq_, tag(1));
    cq_.Next(&got_tag, &ok);
    if (!ok || got_tag != tag(1)) {
        
        // Check error state of channel
        grpc_connectivity_state channel_state = (*channel_).GetState(false);
        switch (channel_state) {
            case grpc_connectivity_state::GRPC_CHANNEL_SHUTDOWN:
            case grpc_connectivity_state::GRPC_CHANNEL_TRANSIENT_FAILURE:
                // Error happend when establishing channel
                throw GrpcRN::Exception::ChannelConnectionFailedException();
                
            case grpc_connectivity_state::GRPC_CHANNEL_CONNECTING:
                // Deadline exceeded
                if (cli_ctx.deadline() < std::chrono::system_clock::now()) {
                    throw GrpcRN::Exception::DeadlineExceededException();
                }
                
            default:
                std::cout << "Unknown error occured while doing gRPC call. Channel state " << channel_state << std::endl;
                // Unkown error happend while connecting
                throw GrpcRN::Exception::UnknownException();
        }
    }
    
    // Send the request of the gRPC call
    grpc::Slice send_slice = grpc::Slice(msg_buf, msg_buf_size);
    std::unique_ptr<grpc::ByteBuffer> send_buffer(new grpc::ByteBuffer(&send_slice, 1));
    call->Write(*send_buffer, tag(2));
    cq_.Next(&got_tag, &ok);
    if (!ok || got_tag != tag(2)) {
        throw GrpcRN::Exception::RequestSendFailedException();
    }
    
    // Try to read the response of the gRPC call
    grpc::ByteBuffer recv_buffer;
    call->Read(&recv_buffer, tag(3));
    cq_.Next(&got_tag, &ok);
    //bool failed_to_recv_buf = !ok || got_tag != tag(3);
    
    // Try to read the status of the gRPC call
    call->Finish(&status, tag(4));
    cq_.Next(&got_tag, &ok);
    bool failed_to_read_status = !ok || got_tag != tag(4);
    
    // If could not read the status of the gRPC call then throw error
    if (failed_to_read_status) {
        
        // Log some error info
        std::cout << "Ok val: " << ok << " got tag: " << got_tag << " expected " << tag(3) << std::endl;
        std::cout << "Failed to finish call." << std::endl;
        
        // Throw error
        throw GrpcRN::Exception::NoStatusSentException();
    }    
    
    // Copy buffer into slice
    grpc::Slice slice;
    auto dumpStatus = recv_buffer.TrySingleSlice(&slice);
    if (!dumpStatus.ok()) {
        recv_buffer.DumpToSingleSlice(&slice);
    }
    
    return slice;
}

void Client::serverStreamingCall(std::string &method_name, uint8_t *msg_buf, size_t msg_buf_size, uint8_t *res_msg_buf, size_t *res_msg_buf_size) {}

void Client::clientStreamingCall(std::string &method_name, uint8_t *msg_buf, size_t msg_buf_size, uint8_t *res_msg_buf, size_t *res_msg_buf_size) {}

void Client::biDirectionalStreamingCall(std::string &method_name, uint8_t *msg_buf, size_t msg_buf_size, uint8_t *res_msg_buf, size_t *res_msg_buf_size) {}

}
