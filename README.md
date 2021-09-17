# React Native gRPC

## A truely native gRPC implementation in React Native

Leverage the performance of the native gRPC libraries in your React Native app.

### How it used to be

If you wanted to use gRPC in a React Native app you would need to use either [grpc-web](https://github.com/grpc/grpc-web) with a proxy infront or make a custom native implemtation of the gRPC libraries for iOS and Android, which can be cumbersome at best.

### What this implementation solves

This implementation utilizes the `protoc` protobuf compilers ability to generate native code AND Javascript. The generated code will communicate with each other through the [NativeModule](https://reactnative.dev/docs/native-modules-intro) interface provided by React Native. This way you can freely communicate with your gRPC backend via Javascript code, without thinking about proxies or other extra worries.

###
