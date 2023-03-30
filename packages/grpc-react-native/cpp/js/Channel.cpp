//
//  Channel.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 28/02/2022.
//

#include "Channel.h"

#include <google/protobuf/descriptor.h>

namespace grpcrn {
namespace js {

using namespace facebook;


Channel::Channel(jsi::Runtime& runtime, jsi::Value* args, size_t count) {
   
    // Make sure there are 2-3 arguments
    if (count >= 2 && count > 3) {
        throw jsi::JSError(runtime, "Channel: Please specify the correct amount of arguments");
        return;
    }
    
    if (!args[0].isString()) {
        throw jsi::JSError(runtime, "Channel: Please specify the correct amount of arguments");
        return;
    }
    
    target_ = args[0].asString(runtime).utf8(runtime);
}

jsi::Value Channel::get(jsi::Runtime &runtime, const jsi::PropNameID &name) {
    auto methodName = name.utf8(runtime);
    
    if (methodName == "setArguments") {
        return jsi::Value::undefined();
    }
    
    if (methodName == "setArguments") {
        return jsi::Value::undefined();
    }
    
    
    return jsi::Value::undefined();
}

void Channel::set(jsi::Runtime &runtime, const jsi::PropNameID &name, const jsi::Value &value) {
    
}

jsi::Value Channel::getTarget(jsi::Runtime& runtime) {
    return jsi::Value(jsi::String::createFromUtf8(runtime, target_));
}

// Static
jsi::Value Channel::create(jsi::Runtime& runtime) {
    return jsi::Value();
}
 
// Static
void Channel::install(jsi::Runtime &rt) {
    
    std::shared_ptr<jsi::HostObject> hostObj(Channel);
    jsi::Function func = jsi::Function::createFromHostFunction(rt, jsi::PropNameID::forAscii(rt, "Channel"), 3, [](jsi::Runtime& runtime, const jsi::Value&, const jsi::Value* arguments, size_t count) -> jsi::Value {
        
        
        return jsi::Value();
    });
}


};
}
