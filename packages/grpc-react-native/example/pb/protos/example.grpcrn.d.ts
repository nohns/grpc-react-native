import type {Client, ChannelCredentials} from 'grpc-react-native';
declare class GreeterClient extends Client {
  private proto: Uint8Array;
  constructor(target: string, channelCredentials: ChannelCredentials);
  SayHello(data: SayHelloRequest): Promise<SayHelloResponse>;
}
declare interface SayHelloRequest {
}
declare interface SayHelloResponse {
}
