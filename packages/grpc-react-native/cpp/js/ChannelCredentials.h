//
//  ChannelCredentials.h
//  Pods
//
//  Created by Asger Nohns on 15/03/2022.
//

#ifndef ChannelCredentials_h
#define ChannelCredentials_h

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "../grpcpp.h"

namespace grpcrn {
namespace js {

using namespace facebook;

class JSI_EXPORT ChannelCredentials : public jsi::HostObject {
public:
    ChannelCredentials(std::shared_ptr<grpc::ChannelCredentials> creds) {
        creds_ = creds;
    }
    
    // Get gRPC credentials
    std::shared_ptr<grpc::ChannelCredentials> getCredentials() {
        return creds_;
    }
    
    static std::shared_ptr<ChannelCredentials> createInsecure() {
        return std::make_shared<ChannelCredentials>(grpc::InsecureChannelCredentials());
    }
private:
    std::shared_ptr<grpc::ChannelCredentials> creds_;
};

    
}
}

#endif /* ChannelCredentials_h */
