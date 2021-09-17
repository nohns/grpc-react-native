# React Native gRPC

## A truely native gRPC implementation for React Native

Leverage the performance of the native gRPC libraries in your React Native app.

### How it used to be

If you wanted to use gRPC in a React Native app you would need to use either [grpc-web](https://github.com/grpc/grpc-web) with a proxy infront or make a custom native implemtation of the gRPC libraries for iOS and Android, which can be cumbersome at best.

Now you can utilize the power of the native libraries right in your javascript, powered by `protc` code generation.

### How it works

This implementation utilizes the `protoc` protobuf compilers ability to generate native and Javascript code. The generated code will communicate with each other through the [NativeModule](https://reactnative.dev/docs/native-modules-intro) interface provided by React Native. This way you can freely communicate with your gRPC backend via Javascript code, without thinking about proxies or other extra worries.

## Getting started

### Step 1: Install dependencies

First of all, you should install the dependencies of the generated code.

#### Javascript

The Javascript code generator depends on these NPM packages that you have to install before generating any code:

`npm install bla bla --save`

Also, install these if you are using Typescript:

`npm install bla bla --save-dev`

#### iOS

Before installing anything, go and add a dummy empty swift file to your project (make sure your app is targeted). Xcode will ask you to create an Objective-C bridging Header. Doing this step prior to installing any Swift dependencies solves some potential build issues. You will also need the bridging header for later

You will need to install [grpc-swift](https://github.com/grpc/grpc-swift) into your React Native Xcode project. Do this via the swift package manager under `Project > Swift Package Manager` and add the url to the above mentioned grpc-swift git repository.

#### Android

Not yet implemented. Feel free to submit a pull with a code generator and docs!

### Step 2: Configuring code generation

For generating all the necessary code, you will need the three (currently only JS and Swift is implemented) plugins from this repository, and a few others

-   `protoc-gen-swift`

    Used for generating the Swift message stubs. [Read more...](https://github.com/apple/swift-protobuf)

-   `protoc-gen-grpc-swift`

    Used for generating the Swift gRPC client stubs. [Read more...](https://github.com/grpc/grpc-swift)

-   `protoc-gen-rn-grpc-swift`

    Used for generating iOS native briding infrastructure. Exposes low level gRPC access to the Javascript of your app. [Read more...](https://github.com/poly-auth/grpc-react-native/tree/main/plugins/swift)

-   `protoc-gen-js`

    Used for generating Javascript message stubs. [Read more...](https://developers.google.com/protocol-buffers/docs/reference/javascript-generated)

-   `protoc-gen-ts` _(Optional)_

    Used in conjunction with `protoc-gen-js`. Generates Typescript definitions for the message stubs. [Read more...](https://github.com/improbable-eng/ts-protoc-gen)

-   `protoc-gen-rn-grpc-js`

    Used for generating Javascript gRPC client stubs. Exposes a high level access to the Native briding infrastructure. Can expose Typescript definitions as well. [Read more...](https://github.com/poly-auth/grpc-react-native/tree/main/plugins/js)

-   ... other plugins for Android (not yet implemented)
