//
//  Client.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 15/03/2022.
//

#include "Client.h"

namespace grpcrn {
namespace js {

static void* tag(int i) { return (void*)(intptr_t)i; }

/// Constructor for gRPC client host object
///
/// Wrapper for the underlying C++ GenericStub, which is making the real calls to the service targeted.
Client::Client(std::shared_ptr<grpcrn::js::lib::PromiseFactory> promiseFactory, jsi::Runtime& runtime, const jsi::Value* args, size_t count): promiseFactory_(promiseFactory) {
    
    // Make sure sufficient arguments are given
    if (count < 2 || count > 3) {
        throw jsi::JSError(runtime, "gRPC Client: two or three arguments needed when creating client stub.");
        return;
    }
    
    // Parse target for this client. The web location where the gRPC service is located
    if (!args[0].isString()) {
        throw jsi::JSError(runtime, "gRPC Client: expected string as first argument.");
        return;
    }
    target_ = args[0].asString(runtime).utf8(runtime);
    
    // Validate channel credentials is a instance of ChannelCredentials host object
    if (!args[1].isObject() || !args[1].asObject(runtime).isHostObject<ChannelCredentials>(runtime)) {
        throw jsi::JSError(runtime, "gRPC Client: expected channel credentials as second argument.");
        return;
    }
    
    // If file descriptor protobuf argument is given, then parse it and use it for this client.
    isGeneric_ = count != 3;
    if (!isGeneric_) {
        // Validate third paramter as a file descriptor proto.
        if (!args[2].isObject() || !args[2].asObject(runtime).isArrayBuffer(runtime)) {
            throw jsi::JSError(runtime, "gRPC Client: expected array buffer as optional third argument.");
            return;
        }
        
        auto fileDescProtoArrayBuf = args[2].asObject(runtime).getArrayBuffer(runtime);
        void* fdpBuf = fileDescProtoArrayBuf.data(runtime);
        size_t fdpBufSize = fileDescProtoArrayBuf.size(runtime);
        
        // Add descriptors to pool from the proto file, in which the service methods for this client is declared
        FileDescriptorProto fdp;
        fdp.ParseFromArray(fdpBuf, (int)fdpBufSize);
        fileDescriptor_ = DescriptorPool().BuildFile(fdp);
    }
    
    // Setup channel to use for this communication
    chanCreds_ = std::make_shared<jsi::Object>(args[1].asObject(runtime));
    auto chanCredsHo = chanCreds_->asHostObject<ChannelCredentials>(runtime);
    chan_ = grpc::CreateChannel(target_, chanCredsHo->getCredentials());
    
    // Create generic stub
    generic_stub_.reset(new grpc::TemplatedGenericStub<grpc::ByteBuffer, grpc::ByteBuffer>(chan_));
}


jsi::Value Client::get(jsi::Runtime& runtime, const jsi::PropNameID& name) {
    std::string mName = name.utf8(runtime);
    
    // Make unary call 
    std::string mNameUnary = "makeUnary";
    if (mName == mNameUnary) {
        return jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, mNameUnary), 2, [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
            
            if (count != 2) {
                throw jsi::JSError(runtime,  "gRPC Client: two arguments need when making unary call.");
            }
            
            // Parse method path
            if (!args[0].isString()) {
                throw jsi::JSError(runtime, "gRPC Client: expected string as first argument.");
            }
            std::string methodPath = args[0].getString(runtime).utf8(runtime);
        
            // Parse data object
            if (!args[1].isObject()) {
                throw jsi::JSError(runtime, "gRPC Client: expected object as last argument.");
            }
            jsi::Object dataObj = args[1].getObject(runtime);
            
            // Return asynchronous promise
            return promiseFactory_->execute(runtime, [this, &runtime, methodPath, &dataObj](std::function<void (jsi::Value)> resolve, std::function<void (std::string &)> reject) -> void {
                try {
                    resolve(makeUnary(runtime, methodPath, dataObj));
                    
                } catch (...) {
                    // TODO: make error handling from the different custom exceptions
                    std::string err = "gRPC Client: Unknown error occured during gRPC call.";
                    reject(err);
                }
            });
        });;
    }
    
    return jsi::Value::undefined();
}

/// Should not be used. Please refer to the "setter" methods created in Messsage::get
void Client::set(jsi::Runtime&, const jsi::PropNameID& name, const jsi::Value& value) {
    
}

// Returns all methods exposed by message. Depends on which protobuf message it represents, which produced the accessible fields.
std::vector<jsi::PropNameID> Client::getPropertyNames(jsi::Runtime& runtime) {
    
    std::vector<jsi::PropNameID> props;
    props.push_back(jsi::PropNameID::forUtf8(runtime, "makeUnary"));
    
    // TODO: return all dynamic methods
    return props;
}

jsi::Value Client::makeUnary(jsi::Runtime& runtime, std::string methodPath, jsi::Object& data) {
    
    // Parse service and method name for lookup request and response protos
    // TODO: optimize
    std::vector<std::string> fileServiceSplit;
    std::vector<std::string> serviceMethodSplit;
    grpcrn::utils::Strings::split(methodPath, '.', fileServiceSplit);
    grpcrn::utils::Strings::split(fileServiceSplit[1], '/', serviceMethodSplit);
    std::string serviceName = serviceMethodSplit[0];
    std::string methodName = serviceMethodSplit[1];
    
    // Find in and out descriptors for method
    auto servDesc = fileDescriptor_->FindServiceByName(serviceName);
    auto methodDesc = servDesc->FindMethodByName(methodName);
    auto inMsgDesc = methodDesc->input_type();
    auto outMsgDesc = methodDesc->output_type();
    
    // Create an empty Message object that will hold the result of deserializing
    // a byte array for the proto definition:
    google::protobuf::DynamicMessageFactory factory;
    const google::protobuf::Message* prototypeInMsg = factory.GetPrototype(inMsgDesc); // prototype_msg is immutable
    const google::protobuf::Message* prototypeOutMsg = factory.GetPrototype(outMsgDesc); // prototype_msg is immutable
    if (prototypeInMsg == NULL || prototypeOutMsg == NULL) {
        // @TODO: Handle error
        std::cerr << "Cannot create prototype message from message descriptor";
        return jsi::Value();
    }
    
    // Create message instances for request and reply
    google::protobuf::Message* req = prototypeInMsg->New();
    google::protobuf::Message* reply = prototypeOutMsg->New();
    if (req == NULL || reply == NULL) {
        // @TODO: Handle error
        std::cerr << "Failed in prototype_msg->New(); to create mutable message";
        return jsi::Value();
    }
    
    // Fill out protobuf data from JS object
    grpcrn::js::pb::Message::mergeObjectIntoProto(runtime, req, data);
    
    // Define generic variables
    grpc::CompletionQueue cq;
    grpc::Status status;
    grpc::ClientContext clientCtx;
    grpc::StubOptions stubOptions;
    void* got_tag;
    bool ok = false;
    
    // Prepare gRPC call
    /*std::unique_ptr<grpc::ClientAsyncReaderWriter<grpc::ByteBuffer, grpc::ByteBuffer>> call = generic_stub_->PrepareCall(&clientCtx, methodPath, &cq);*/
    
    grpc::Slice reqSlices[] = {grpc::Slice(req->SerializeAsString())};
    grpc::ByteBuffer reqBuffer(reqSlices, 1);
    grpc::ByteBuffer replyBuffer;
    
    generic_stub_->UnaryCall(&clientCtx, methodPath, stubOptions, &reqBuffer, &replyBuffer, [this, &clientCtx](grpc::Status status) -> void {
        if (!status.ok()) {
            // Check error state of channel
            grpc_connectivity_state channel_state = this->chan_->GetState(false);
            switch (channel_state) {
                case grpc_connectivity_state::GRPC_CHANNEL_SHUTDOWN:
                case grpc_connectivity_state::GRPC_CHANNEL_TRANSIENT_FAILURE:
                    // Error happend when establishing channel
                    throw ChannelConnectionFailedException();
                    
                case grpc_connectivity_state::GRPC_CHANNEL_CONNECTING:
                    // Deadline exceeded
                    if (clientCtx.deadline() < std::chrono::system_clock::now()) {
                        throw DeadlineExceededException();
                    }
                    
                default:
                    std::cout << "Unknown error occured while doing gRPC call. Channel state " << channel_state << std::endl;
                    std::cout << "error = " << status.error_code() << ": " << status.error_message() << " (" << status.error_details() << ")" << std::endl;
                    // Unkown error happend while connecting
                    throw UnknownException();
            }
            
            return;
        }
        
    });
    
    grpc::Slice replySlice;
    replyBuffer.DumpToSingleSlice(&replySlice);
    reply->ParseFromArray(replySlice.begin(), (int)replySlice.size());
    
    // Start grpc call
    /*call->StartCall(tag(1));
    cq.Next(&got_tag, &ok);
    if (!ok || got_tag != tag(1)) {
        
        // Check error state of channel
        grpc_connectivity_state channel_state = chan_->GetState(false);
        switch (channel_state) {
            case grpc_connectivity_state::GRPC_CHANNEL_SHUTDOWN:
            case grpc_connectivity_state::GRPC_CHANNEL_TRANSIENT_FAILURE:
                // Error happend when establishing channel
                throw ChannelConnectionFailedException();
                
            case grpc_connectivity_state::GRPC_CHANNEL_CONNECTING:
                // Deadline exceeded
                if (clientCtx.deadline() < std::chrono::system_clock::now()) {
                    throw DeadlineExceededException();
                }
                
            default:
                std::cout << "Unknown error occured while doing gRPC call. Channel state " << channel_state << std::endl;
                // Unkown error happend while connecting
                throw UnknownException();
        }
    }
    
    // Send the request of the gRPC call
    call->Write(*req, tag(2));
    cq.Next(&got_tag, &ok);
    if (!ok || got_tag != tag(2)) {
        throw RequestSendFailedException();
    }
    
    // Try to read the response of the gRPC call
    call->Read(reply, tag(3));
    cq.Next(&got_tag, &ok);
    //bool failed_to_recv_buf = !ok || got_tag != tag(3);
    
    // Try to read the status of the gRPC call
    call->Finish(&status, tag(4));
    cq.Next(&got_tag, &ok);
    bool failed_to_read_status = !ok || got_tag != tag(4);
    
    // If could not read the status of the gRPC call then throw error
    if (failed_to_read_status) {
        
        // Log some error info
        std::cout << "Ok val: " << ok << " got tag: " << got_tag << " expected " << tag(3) << std::endl;
        std::cout << "Failed to finish call." << std::endl;
        
        // Throw error
        throw NoStatusSentException();
    }*/
    
    // Parse reply proto into jsi host object message format
    std::shared_ptr<grpcrn::js::pb::Message> msgHo = std::make_shared<grpcrn::js::pb::Message>();
    msgHo->parseFromProto(runtime, *reply);
    
    // Return js object value
    auto msgJs = jsi::Object::createFromHostObject(runtime, msgHo);
    return jsi::Value(std::move(msgJs));
}

// Not in use just yet
void Client::prepareRpcs() {
    
}



}}
