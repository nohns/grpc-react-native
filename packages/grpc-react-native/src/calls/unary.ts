import { translateError } from '../calls';

export async function makeUnaryCall(
  clientHandle: number,
  methodName: string,
  request: Uint8Array
): Promise<Uint8Array> {
  try {
    const resBuffer = await GrpcReactNative.makeUnaryCall(
      clientHandle,
      methodName,
      request.buffer
    );

    return new Uint8Array(resBuffer);
  } catch (err) {
    throw translateError(err);
  }
}
