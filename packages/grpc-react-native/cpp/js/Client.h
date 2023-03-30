//
//  Client.h
//  Pods
//
//  Created by Asger Nohns on 15/03/2022.
//

#ifndef Client_h
#define Client_h

#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>

#include "../grpcpp.h"
#include "pb/Message.h"
#include "lib/PromiseFactory.h"
#include "ChannelCredentials.h"
#include "thread-pool.h"
#include "../utils/Strings.h"

#include <iostream>
 


namespace grpcrn {
namespace js {

using namespace facebook;
using namespace google::protobuf;

class JSI_EXPORT Client : public jsi::HostObject {
public:
    Client(std::shared_ptr<grpcrn::js::lib::PromiseFactory> promiseFactory, jsi::Runtime& runtime, const jsi::Value* args, size_t count);
    
    // Implement host object methods for communicating with JS.
    /// Defines all methods available on the generic gRPC client exposed in JS
    jsi::Value get(jsi::Runtime&, const jsi::PropNameID& name) override;
    ///  Not used. There is no properties to set on the client from JS. Use the methods exposed by Client::get
    void set(jsi::Runtime&, const jsi::PropNameID& name, const jsi::Value& value) override;
    /// Get all methods names exposed to JS.
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
    
    // gRPC client specific methods
    jsi::Value makeUnary(jsi::Runtime& runtime, std::string methodName, jsi::Object& data);
private:
    bool isGeneric_;
    std::string target_;
    
    // Reference to channel credentials. Can be safely unwrapped as ChannelCredentials HostObject
    std::shared_ptr<jsi::Object> chanCreds_;
    
    // Reference to channel
    std::shared_ptr<grpc::Channel> chan_;
    
    // Generic gRPC stub, to make the calls to the external service
    std::unique_ptr<grpc::TemplatedGenericStub<grpc::ByteBuffer, grpc::ByteBuffer>> generic_stub_;
    
    // Provides reference to the shared promise factory used when creating async js promises. Uses concurrent threading
    std::shared_ptr<grpcrn::js::lib::PromiseFactory> promiseFactory_;
    
    // File descriptor containing information about the service which the client is consuming
    const FileDescriptor* fileDescriptor_;
    std::unordered_map<string, google::protobuf::Message*> reqProtos_;
    std::unordered_map<string, google::protobuf::Message*> resProtos_;
    
    void prepareRpcs();
};


class GenericException : public std::exception {
public:
    virtual const char* type() {
        return "GenericError";
    }
};


class ChannelConnectionFailedException : public GenericException
{
public:
    virtual const char* type() {
        return "ChannelConnectionFailedError";
    }
    
    virtual const char* what() const throw()
    {
        return "A connection could not be made to the gRPC server through the channel";
    }
};

class DeadlineExceededException : public GenericException
{
public:
    virtual const char* type() {
        return "DeadlineExceededError";
    }
    
    virtual const char* what() const throw()
    {
        return "Deadline exceeded during gRPC call";
    }
};

class RequestSendFailedException : public GenericException
{
public:
    virtual const char* type() {
        return "RequestSendFailedError";
    }
    
    virtual const char* what() const throw()
    {
        return "The gRPC request could not be sent";
    }
};

class NoStatusSentException : public GenericException
{
public:
    virtual const char* type() {
        return "NoStatusSentError";
    }
    
    virtual const char* what() const throw()
    {
        return "A status was not sent in the gRPC call answer";
    }
};

class UnknownException : public GenericException
{
public:
    virtual const char* type() {
        return "UnknownError";
    }
    
    virtual const char* what() const throw()
    {
        return "An unknown error occured while trying to call gRPC service";
    }
};

}
}


#endif /* Client_h */
