// Reference to gRPC channel on the native side
export class Channel {
  constructor(public readonly handle: number) {}

  static createInsecure(address: string) {
    return new Channel(GrpcReactNative.createInsecureChannel(address));
  }
}
