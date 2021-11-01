import { makeUnaryCall } from './calls/unary';
import type { Channel } from './channel';

export abstract class Client {
  private readonly handle: number;

  constructor(channel: Channel) {
    this.handle = GrpcReactNative.createClient(channel.handle);
  }

  // Makes a unary call to the specified method with this client
  protected _makeUnaryCall(methodName: string, request: Uint8Array) {
    return makeUnaryCall(this.handle, methodName, request);
  }
}
