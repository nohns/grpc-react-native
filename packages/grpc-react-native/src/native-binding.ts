// Native functions exposed by jsi bridge. See cpp/grpc-rn-module.cpp
import type { ChannelCredentialsStub } from './channel-credentials';
import type { ClientStub } from './client';

declare const GrpcReactNative: {
  createInsecureChannelCredentials(): ChannelCredentialsStub;
  createClient(
    target: string,
    clientCredentialsStub: ChannelCredentialsStub,
    protoDefinitions?: ArrayBuffer
  ): ClientStub;
};

export const GRPCRN = GrpcReactNative;
