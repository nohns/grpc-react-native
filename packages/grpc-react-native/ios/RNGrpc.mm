//
//  grpc-rn-ios.mm
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#import "RNGrpc.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <jsi/jsi.h>
#import <stdio.h>
#import "GRPCRTNModule.h"

@interface RCTBridge (ext)
- (std::shared_ptr<facebook::react::CallInvoker>)jsCallInvoker;
- (std::shared_ptr<facebook::react::CallInvoker>)decorateNativeCallInvoker;
@end


@implementation RNGrpc

using namespace facebook;
using namespace std;

@synthesize bridge = _bridge;
@synthesize methodQueue = _methodQueue;

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup {
    
    return YES;
}

- (void)setBridge:(RCTBridge *)bridge {
    _bridge = bridge;
    _setBridgeOnMainQueue = RCTIsMainQueue();
    
    [self installLibrary];
}

- (void)installLibrary {
    
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
    
    
    if (!cxxBridge.runtime) {
        /**
         * This is a workaround to install library
         * as soon as runtime becomes available and is
         * not recommended. If you see random crashes in iOS
         * global.xxx not found etc. use this.
         */
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.001 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
            /**
             * When refreshing the app while debugging, the setBridge
             * method is called too soon. The runtime is not ready yet
             * quite often. We need to install library as soon as runtime
             * becomes available.
             */
            [self installLibrary];
            
        });
        return;
    }
    
    // Install grpc-react-native c++ module
    grpcrn::GRPCRTNModule::install(*(jsi::Runtime *)cxxBridge.runtime, cxxBridge.jsCallInvoker);
}

@end
