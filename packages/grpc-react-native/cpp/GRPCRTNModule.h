//
//  GRPCRTNModule.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#ifndef grpcrn_GRPCRTNModule_h
#define grpcrn_GRPCRTNModule_h

#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>

#include "grpc-rn-manager.h"
#include "grpc-rn-client.h"
#include "thread-pool.h"
#include "js/lib/PromiseFactory.h"

namespace grpcrn {

using namespace facebook;

class JSI_EXPORT GRPCRTNModule : public jsi::HostObject {
public:
    GRPCRTNModule(std::shared_ptr<react::CallInvoker> jsCallInvoker);
    static void install(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> jsCallInvoker);
    
    // Host object overrides
    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
    
private:
    std::shared_ptr<grpcrn::js::lib::PromiseFactory> promiseFactory_;
    
    //facebook::jsi::Value jsiGrpcRNMakeUnaryCall(facebook::jsi::Runtime& runtime, long clientHandle, std::string& methodName, uint8_t* reqBuf, size_t& reqBufSize);
};


}


#endif /* grpcrn_GRPCRTNModule_h */
