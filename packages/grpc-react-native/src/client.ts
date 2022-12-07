import type { ChannelCredentials } from './channel-credentials';
import { GRPCRN } from './native-binding';

export interface ClientStub {
  makeUnaryCall<TReq, TRes>(method: string, data: TReq): Promise<TRes>;
}

export abstract class Client {
  // @ts-expect-error
  private readonly client: ClientStub;

  constructor(
    target: string,
    channelCredentials: ChannelCredentials,
    protoDefinitions?: ArrayBuffer
  ) {
    this.client = GRPCRN.createClient(
      target,
      channelCredentials.getStub(),
      protoDefinitions
    );
  }
}
