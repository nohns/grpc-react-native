// Native functions exposed by jsi bridge. See cpp/grpc-rn-module.cpp
declare const GrpcReactNative: {
  createInsecureChannel(addr: string): number;
  createClient(channelHandle: number): number;
  makeUnaryCall(
    clientHandle: number,
    methodName: string,
    request: ArrayBuffer
  ): Promise<ArrayBuffer>;
};
