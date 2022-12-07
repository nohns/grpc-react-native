//
//  Channel.h
//  grpc-react-native
//
//  Created by Asger Nohns on 28/02/2022.
//

#ifndef Channel_h
#define Channel_h

#include "../grpcpp.h"
#include <jsi/jsilib.h>
#include <jsi/jsi.h>

namespace grpcrn {
namespace js {

using namespace facebook;

class Channel : public jsi::HostObject
{
public:
    Channel(jsi::Runtime& runtime, jsi::Value* args, size_t count);
    
    
    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;
    void set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value) override;
    
    static jsi::Value create(jsi::Runtime& runtime);
    static void install(jsi::Runtime& runtime);
private:
    std::shared_ptr<grpc::ChannelInterface> channel_;
    
    std::string target_;
    
    void close();
    
    jsi::Value getTarget(jsi::Runtime& runtime);
    jsi::Value getConnectivityState(bool reconnect);
};

}
}

#endif /* Channel_h */
