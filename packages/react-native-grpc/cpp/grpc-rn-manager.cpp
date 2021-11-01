//
//  grpc-rn-manager.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#include "grpc-rn-manager.h"

namespace GrpcRN {

long Manager::createInsecureChannel(std::string addr) {
    long handle = channels_.size();
    
    // Create new channcel
    channels_[handle] = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    
    // Return handle for channel
    return handle;
}

long Manager::createClient(long channelHandle) {
    
    // Get connection from handle
    auto channel = channels_[channelHandle];
    
    // Create client
    long handle = clients_.size();
    clients_[handle] = new GrpcRN::Client(channel);
    
    return handle;
}

GrpcRN::Client* Manager::getClient(long clientHandle) {
    return clients_[clientHandle];
}

}
