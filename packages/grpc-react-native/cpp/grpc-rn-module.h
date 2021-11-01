//
//  grpc-rn-module.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#ifndef grpc_rn_module_h
#define grpc_rn_module_h

#include "grpc-rn-manager.h"
#include "grpc-rn-client.h"

#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include "thread-pool.h"


#include <ReactCommon/CallInvoker.h>

namespace GrpcRN {

using namespace facebook;

class JSI_EXPORT GrpcRNModule : public jsi::HostObject {
public:
    
    GrpcRNModule(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> jsCallInvoker);
    
    static void install(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> jsCallInvoker);
    
    /*
     * `jsi::HostObject` specific overloads.
     */
    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;

    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
    
private:
    jsi::Runtime& runtime_;
    std::shared_ptr<react::CallInvoker> jsCallInvoker_;
    ThreadPool threadPool_;
    
    facebook::jsi::Value jsiGrpcRNMakeUnaryCall(facebook::jsi::Runtime& runtime, long clientHandle, std::string& methodName, uint8_t* reqBuf, size_t& reqBufSize);
};


}


#endif /* grpc_rn_module_h */
