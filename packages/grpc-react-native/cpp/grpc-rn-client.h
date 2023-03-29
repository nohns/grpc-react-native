//
//  grpc-rn-client.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#ifndef client_hpp
#define client_hpp

#include "grpcpp.h"

namespace GrpcRN {

class Client {
public:
    
    // Client constructor
    Client(std::shared_ptr<grpc::ChannelInterface> channel);
    
    grpc::Slice unaryCall(grpc::Status& status, std::string method_name, uint8_t* msg_buf, size_t msg_buf_size);
    
    void serverStreamingCall(std::string &method_name, uint8_t *msg_buf, size_t msg_buf_size, uint8_t *res_msg_buf, size_t *res_msg_buf_size);
    
    void clientStreamingCall(std::string &method_name, uint8_t *msg_buf, size_t msg_buf_size, uint8_t *res_msg_buf, size_t *res_msg_buf_size);
    
    void biDirectionalStreamingCall(std::string &method_name, uint8_t *msg_buf, size_t msg_buf_size, uint8_t *res_msg_buf, size_t *res_msg_buf_size);
    
private:
    grpc::CompletionQueue cq_;
    std::unique_ptr<grpc::GenericStub> generic_stub_;
    std::shared_ptr<grpc::ChannelInterface> channel_;
    
    
};
}

#endif /* client_hpp */
