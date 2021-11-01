//
//  grpc-rn-ios.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#import <React/RCTBridgeModule.h>

@interface RNGrpc : NSObject <RCTBridgeModule>;

@property(nonatomic, assign) BOOL setBridgeOnMainQueue;

@end
