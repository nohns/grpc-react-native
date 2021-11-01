//
//  grpc-rn-manager.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "grpcpp.h"
#include "grpc-rn-client.h"

namespace GrpcRN {

class Manager {
public:
    
    /**
     * Creates a new insecure connection to gRPC server at the given address. Channel handle is returned
     */
    long createInsecureChannel(std::string addr);
    
    /**
     * Creates a client instance that is able to make gRPC requests. Client handle is returned
     */
    long createClient(long channelHandle);
    
    
    GrpcRN::Client* getClient(long clientHandle);
    
    /**
     * Access the shared singleton instance of the gRPC manager for React Native
     */
    static Manager* instance() {
        
        // If shared manager has not been initialized yet, set it now
        if (instance_ == nullptr) {
            instance_ = new Manager();
        }
        
        return instance_;
    }
private:
    static Manager* instance_;
    
    /**
     * Map for holdning all active connections created from the js side
     */
    std::map<long, std::shared_ptr<grpc::Channel>> channels_;
    
    /**
     * Map for holdning all active clients created from the js side
     */
    std::map<long, GrpcRN::Client*> clients_;
};

Manager* Manager::instance_ = nullptr;

}

#endif /* EXAMPLE_H */
