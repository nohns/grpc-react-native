import { GRPCRN } from './native-binding';

export interface ChannelCredentialsStub {}

export class ChannelCredentials {
  #_stub: ChannelCredentialsStub;

  constructor(stub: ChannelCredentialsStub) {
    this.#_stub = stub;
  }

  getStub() {
    return this.#_stub;
  }

  static createInsecure() {
    return new ChannelCredentials(GRPCRN.createInsecureChannelCredentials());
  }

  static createSSL() {
    // TODO: Implement SSL channel credentials
    return new ChannelCredentials(GRPCRN.createInsecureChannelCredentials());
  }
}
