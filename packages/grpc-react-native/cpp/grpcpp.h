//
//  grpcpp.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#ifndef grpcpp_h
#define grpcpp_h

// Make sure the right library is included for the platform
#ifdef __ANDROID__
// Android Headers
#elif __APPLE__
// iOS Headers
#import <grpcpp/grpcpp.h>

#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/generic/generic_stub.h>

#endif /* __ANDROID__ elseif __APPLE__*/

#endif /* grpcpp_h */
