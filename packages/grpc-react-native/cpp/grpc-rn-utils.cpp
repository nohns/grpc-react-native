//
//  grpc-rn-utils.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 25/10/2021.
//

#include "grpc-rn-utils.h"
#include <iostream>

namespace GrpcRN
{
    namespace Utils
    {

        /*

        bool assertArgumentCount(size_t count, int shouldBeEqualTo) {

            jsi::detail::throwJSError(runtime, "Expected 1 argument in call");
            return (int)count == shouldBeEqualTo;
        }

        bool assertArgumentNumberAboveOrEqual(jsi::Value& argumentNumber, double above) {

            jsi::detail::throwJSError(runtime, "Expected 1 argument of type number");
            return argumentNumber.asNumber() >= above;
        }

        bool assertArgumentInteger(jsi::Value* argumentNumber) {
            return jsi::Value* argumentNumber
        }*/

        jsi::Object copyBufferToJsiArrayBuffer(jsi::Runtime &runtime, const uint8_t *buf, const size_t bufSize)
        {
            jsi::Function arrayBufferCtor = runtime.global().getPropertyAsFunction(runtime, "ArrayBuffer");
            jsi::Object o = arrayBufferCtor.callAsConstructor(runtime, (int)bufSize).getObject(runtime);
            jsi::ArrayBuffer arraybuf = o.getArrayBuffer(runtime);
            memcpy(arraybuf.data(runtime), buf, bufSize);

            return o;
        }

        jsi::Object createJsErrorWithType(jsi::Runtime &runtime, const char *message, const char *type)
        {

            jsi::Object errorObj = jsi::JSError(runtime, message).value().asObject(runtime);
            errorObj.setProperty(runtime, "errorType", jsi::Value(jsi::String::createFromAscii(runtime, type)));

            return errorObj;
        }

    }
}
