//
//  grpc-rn-utils.h
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#ifndef grpc_rn_utils_h
#define grpc_rn_utils_h

#include <jsi/jsi.h>
#include <stdio.h>

using namespace facebook;

namespace GrpcRN
{
    namespace Utils
    {

        jsi::Object copyBufferToJsiArrayBuffer(jsi::Runtime &runtime, const uint8_t *buf, const size_t bufSize);

        jsi::Object createJsErrorWithType(jsi::Runtime &runtime, const char *message, const char *type);
    }
}

#endif /* grpc_rn_utils_h */
