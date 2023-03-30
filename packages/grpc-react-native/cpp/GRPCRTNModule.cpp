//
//  GRPCRTNModule.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//
#include "GRPCRTNModule.h"
#include "grpcpp.h"

//#include "js/Client.h"
//#include "js/ChannelCredentials.h"

using namespace facebook;

namespace grpcrn
{

GRPCRTNModule::GRPCRTNModule(std::shared_ptr<react::CallInvoker> jsCallInvoker) {
    promiseFactory_ = std::make_shared<grpcrn::js::lib::PromiseFactory>(jsCallInvoker);
}

jsi::Value GRPCRTNModule::get(jsi::Runtime &runtime, const jsi::PropNameID &propName) {
    auto name = propName.utf8(runtime);
    
    if (name == "createInsecureChannel")
    {
        return jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, "createInsecureChannel"), 1, [](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value {
            /*auto chanCredsHo = grpcrn::js::ChannelCredentials::createInsecure();
            auto chanCredsJs = jsi::Object::createFromHostObject(runtime, chanCredsHo);
            
            return jsi::Value(std::move(chanCredsHo));*/
            return jsi::Value::undefined();
        });
    }
    
    if (name == "createClient")
    {
        return jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, "createClient"), 3, [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
            /*auto clientHo = std::make_shared<grpcrn::js::Client>(this->promiseFactory_, runtime, arguments, count);
            auto clientJs = jsi::Object::createFromHostObject(runtime, clientHo);
            
            return jsi::Value(std::move(clientJs));*/
            return jsi::Value::undefined();
            
        });
    }
    
    /*if (name == "makeUnaryCall")
     {
     return jsi::Function::createFromHostFunction(runtime_, jsi::PropNameID::forAscii(runtime_, "makeUnaryCall"), 3, [this](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
     {
     
     // Make sure we do have 3 arguments of the right types
     if (count != 3 || !arguments[0].isNumber() || !arguments[1].isString() || !arguments[2].isObject() || !arguments[2].asObject(runtime).isArrayBuffer(runtime)) {
     throw jsi::JSError(runtime, "Expected 3 arguments of type number, string and ArrayBuffer");
     }
     
     // Get client handle
     // Make sure we have a possible integer
     double clientHandleDouble = arguments[0].asNumber();
     long clientHandle = std::lround(clientHandleDouble);
     if (clientHandle < 0) {
     throw jsi::JSError(runtime, "Expected first argument to be an unsigned integer");
     }
     
     // Get method name
     std::string methodName = arguments[1].asString(runtime).utf8(runtime);
     
     // Get buffer
     auto arrayBuf = arguments[2].asObject(runtime).getArrayBuffer(runtime);
     uint8_t* buf = arrayBuf.data(runtime);
     size_t bufSize = arrayBuf.size(runtime);
     
     return this->jsiGrpcRNMakeUnaryCall(runtime, clientHandle, methodName, buf, bufSize); });
     }*/
    
    return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> GRPCRTNModule::getPropertyNames(jsi::Runtime &runtime)
{
    std::vector<jsi::PropNameID> result;
    result.push_back(jsi::PropNameID::forUtf8(runtime, std::string("createInsecureChannel")));
    result.push_back(jsi::PropNameID::forUtf8(runtime, std::string("createClient")));
    //result.push_back(jsi::PropNameID::forUtf8(runtime, std::string("makeUnaryCall")));
    return result;
}

void GRPCRTNModule::install(jsi::Runtime &runtime, std::shared_ptr<react::CallInvoker> jsCallInvoker)
{
    auto jsiModule = std::make_shared<GRPCRTNModule>(jsCallInvoker);
    auto object = jsi::Object::createFromHostObject(runtime, jsiModule);
    runtime.global().setProperty(runtime, "GrpcReactNative", jsi::Value(std::move(object)));
}

/*jsi::Value GRPCRTNModule::jsiGrpcRNMakeUnaryCall(jsi::Runtime &runtime, long clientHandle, std::string &methodName, uint8_t *reqBuf, size_t &reqBufSize)
{
    
    // Define promise actions
    auto promiseCallback = [this, &clientHandle, &methodName, reqBuf, &reqBufSize](jsi::Runtime &runtime, const jsi::Value &, const jsi::Value *arguments, size_t count) -> jsi::Value
    {
        // Make sure the promise callback is in the right format
        if (count != 2)
        {
            throw std::runtime_error("Promise Callback called with an unexpected amount of arguments!");
        }
        auto resolver = std::make_shared<jsi::Function>(arguments[0].asObject(runtime).asFunction(runtime));
        auto rejecter = std::make_shared<jsi::Function>(arguments[1].asObject(runtime).asFunction(runtime));
        
        threadPool_.enqueue([this, &runtime, clientHandle, methodName, &reqBuf, reqBufSize, resolver, rejecter]()
                            {
            
            try {
                // Find client
                auto client = GrpcRN::Manager::instance()->getClient(clientHandle);
                
                // Make unary call
                grpc::Status status;
                grpc::Slice unaryRes = client->unaryCall(status, methodName, reqBuf, reqBufSize);
                
                // If an error was returned by the gRPC method then reject promise with js error
                if (!status.ok()) {
                    auto code    = status.error_code();
                    auto message = status.error_message();
                    
                    this->jsCallInvoker_->invokeAsync([&runtime, rejecter, message, code]() {
                        
                        jsi::Object errorObj = GrpcRN::Utils::createJsErrorWithType(runtime, message.c_str(), "StatusError");
                        errorObj.setProperty(runtime, "code", jsi::Value((int)code));
                        rejecter->call(runtime, jsi::Value(std::move(errorObj)), 1);
                    });
                    
                } catch (std::exception& exception) {
                    auto message = std::string("Failed to execute gRPC message! ") + std::string(exception.what());
                    
                    this->jsCallInvoker_->invokeAsync([&runtime, rejecter, message](){
                        
                        auto error = jsi::JSError(runtime, message);
                        std::cout << "gRPC call failed: " << message << std::endl;
                        rejecter->call(runtime, error.value(), 1);
                    });
                    
                } catch (...) {
                    auto message = std::string("Unknown gRPC error occured");
                    
                    this->jsCallInvoker_->invokeAsync([&runtime, rejecter, message](){
                        
                        auto error = jsi::JSError(runtime, message);
                        std::cout << "Unknown gRPC error occured" << std::endl;
                        rejecter->call(runtime, error.value(), 1);
                    });
                }
                
                // Make sure that we notify the js thread when we invoke the promise resolve callback
                this->jsCallInvoker_->invokeAsync([&runtime, resolver, unaryRes]() {
                    
                    jsi::Object resArrayBufObject = GrpcRN::Utils::copyBufferToJsiArrayBuffer(runtime, unaryRes.begin(), unaryRes.size());
                    
                    // Resolve promise
                    auto responseObjValue = jsi::Value(std::move(resArrayBufObject));
                });
                
            } catch (GrpcRN::Exception::GenericException& exp) {
                
                auto errorType = exp.type();
                auto errorMessage = exp.what();
                
                this->jsCallInvoker_->invokeAsync([&runtime, rejecter, errorType, errorMessage](){
                    
                    jsi::Object errorObj = GrpcRN::Utils::createJsErrorWithType(runtime, errorMessage, errorType);
                    rejecter->call(runtime, jsi::Value(std::move(errorObj)), 1);
                });
                
            } catch (std::exception& exception) {
                auto message = std::string("Failed to execute gRPC message! ") + std::string(exception.what());
                
                this->jsCallInvoker_->invokeAsync([&runtime, rejecter, message](){
                    
                    auto error = jsi::JSError(runtime, message);
                    std::cout << "gRPC call failed: " << message << std::endl;
                    rejecter->call(runtime, error.value(), 1);
                });
                
            } catch (...) {
                auto message = std::string("Unknown gRPC error occured");
                
                this->jsCallInvoker_->invokeAsync([&runtime, rejecter, message](){
                    
                    auto error = jsi::JSError(runtime, message);
                    std::cout << "Unknown gRPC error occured" << std::endl;
                    rejecter->call(runtime, error.value(), 1);
                });
            } });
        
        return jsi::Value::undefined();
    };
    
    // Create promise from callback
    auto promiseCtor = runtime.global().getPropertyAsFunction(runtime, "Promise");
    auto promise = jsi::Value(promiseCtor.callAsConstructor(runtime, jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, "PromiseCallback"), 2, std::move(promiseCallback))).asObject(runtime));
    
    // Return response
    return promise;
}*/

}
