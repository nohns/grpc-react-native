/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * Generated with the TypeScript template
 * https://github.com/react-native-community/react-native-template-typescript
 *
 * @format
 */

import React, {useState} from 'react';
import {
  ActivityIndicator,
  Alert,
  SafeAreaView,
  StatusBar,
  StyleSheet,
  Text,
  TouchableOpacity,
  View,
} from 'react-native';
import {ChannelCredentials} from '../lib/typescript';

import {
  GetProductFromBarcodeRequest,
  GetProductFromBarcodeResponse,
} from './jspb/stylekorean_pb';
import {GreeterClient} from './pb/protos/example.grpcrn';

declare const GrpcReactNative: {
  createInsecureChannel(addr: string): number;
  createClient(channelHandle: number): number;
  makeUnaryCall(
    clientHandle: number,
    methodName: string,
    request: ArrayBuffer,
  ): Promise<ArrayBuffer>;
};

const c = new GreeterClient('target', ChannelCredentials.createInsecure());
c.SayHello({});

class Channel {
  constructor(public readonly handle: number) {}

  static createInsecure(address: string) {
    return new Channel(GrpcReactNative.createInsecureChannel(address));
  }
}

class UnknownError extends Error {
  name: string = 'UnknownError';
}

class DeadlineExceededError extends Error {
  name: string = 'DeadlineExceededError';
}

class ChannelConnectionFailedError extends Error {
  name: string = 'ChannelConnectionFailedError';
}

class NoStatusSentError extends Error {
  name: string = 'NoStatusSentError';
}

class RequestSendFailedError extends Error {
  name: string = 'RequestSendFailedError';
}

class StatusError extends Error {
  grpcType: string = '';

  get name(): string {
    return this.grpcType + 'StatusError';
  }
  code?: number;
}

class CancelledStatusError extends StatusError {
  grpcType: string = 'Cancelled';
  code: number = 1;
}

/**
 * Unknown error. An example of where this error may be returned is if a
 * Status value received from another address space belongs to an error-space
 * that is not known in this address space. Also errors raised by APIs that
 * do not return enough error information may be converted to this error.
 */
class UnknownStatusError extends StatusError {
  grpcType: string = 'Unknown';
  code: number = 2;
}

/**
 * Client specified an invalid argument. Note that this differs from
 * FAILED_PRECONDITION. INVALID_ARGUMENT indicates arguments that are
 * problematic regardless of the state of the system (e.g., a malformed file
 * name).
 */
class InvalidArgumentStatusError extends StatusError {
  grpcType: string = 'InvalidArgument';
  code: number = 3;
}

/**
 * Deadline expired before operation could complete. For operations that
 * change the state of the system, this error may be returned even if the
 * operation has completed successfully. For example, a successful response
 * from a server could have been delayed long enough for the deadline to
 * expire.
 */
class DeadlineExceededStatusError extends StatusError {
  grpcType: string = 'DeadlineExceeded';
  code: number = 4;
}

/**
 * Some requested entity (e.g., file or directory) was not found.
 */
class NotFoundStatusError extends StatusError {
  grpcType: string = 'NotFound';
  code: number = 5;
}

/**
 * Some entity that we attempted to create (e.g., file or directory) already
 * exists.
 */
class AlreadyExistsStatusError extends StatusError {
  grpcType: string = 'AlreadyExists';
  code: number = 6;
}

/**
 * The caller does not have permission to execute the specified operation.
 * PERMISSION_DENIED must not be used for rejections caused by exhausting
 * some resource (use RESOURCE_EXHAUSTED instead for those errors).
 * PERMISSION_DENIED must not be used if the caller can not be identified
 * (use UNAUTHENTICATED instead for those errors).
 */
class PermissionDeniedStatusError extends StatusError {
  grpcType: string = 'PermissionDenied';
  code: number = 7;
}

/**
 * The request does not have valid authentication credentials for the
 * operation.
 */
class UnauthenticatedStatusError extends StatusError {
  grpcType: string = 'Unauthenticated';
  code: number = 16;
}

/**
 * Some resource has been exhausted, perhaps a per-user quota, or perhaps the
 * entire file system is out of space.
 */
class ResourceExhaustedStatusError extends StatusError {
  grpcType: string = 'ResourceExhausted';
  code: number = 8;
}

/**
 * Operation was rejected because the system is not in a state required for
 * the operation's execution. For example, directory to be deleted may be
 * non-empty, an rmdir operation is applied to a non-directory, etc.
 *
 * A litmus test that may help a service implementor in deciding
 * between FAILED_PRECONDITION, ABORTED, and UNAVAILABLE:
 *   (a) Use UNAVAILABLE if the client can retry just the failing call.
 *   (b) Use ABORTED if the client should retry at a higher-level
 *       (e.g., restarting a read-modify-write sequence).
 *   (c) Use FAILED_PRECONDITION if the client should not retry until
 *       the system state has been explicitly fixed. E.g., if an "rmdir"
 *       fails because the directory is non-empty, FAILED_PRECONDITION
 *       should be returned since the client should not retry unless
 *       they have first fixed up the directory by deleting files from it.
 *   (d) Use FAILED_PRECONDITION if the client performs conditional
 *       REST Get/Update/Delete on a resource and the resource on the
 *       server does not match the condition. E.g., conflicting
 *       read-modify-write on the same resource.
 */
class FailedPreconditionStatusError extends StatusError {
  grpcType: string = 'FailedPrecondition';
  code: number = 9;
}

/**
 * The operation was aborted, typically due to a concurrency issue like
 * sequencer check failures, transaction aborts, etc.
 *
 * See litmus test above for deciding between FAILED_PRECONDITION, ABORTED,
 * and UNAVAILABLE.
 */
class AbortedStatusError extends StatusError {
  grpcType: string = 'Aborted';
  code: number = 10;
}

/**
 * Operation was attempted past the valid range. E.g., seeking or reading
 * past end of file.
 *
 * Unlike INVALID_ARGUMENT, this error indicates a problem that may be fixed
 * if the system state changes. For example, a 32-bit file system will
 * generate INVALID_ARGUMENT if asked to read at an offset that is not in the
 * range [0,2^32-1], but it will generate OUT_OF_RANGE if asked to read from
 * an offset past the current file size.
 *
 * There is a fair bit of overlap between FAILED_PRECONDITION and
 * OUT_OF_RANGE. We recommend using OUT_OF_RANGE (the more specific error)
 * when it applies so that callers who are iterating through a space can
 * easily look for an OUT_OF_RANGE error to detect when they are done.
 */
class OutOfRangeStatusError extends StatusError {
  grpcType: string = 'OutOfRange';
  code: number = 11;
}

/**
 * Operation is not implemented or not supported/enabled in this service.
 */
class UnimplementedStatusError extends StatusError {
  grpcType: string = 'Unimplemented';
  code: number = 12;
}

/**
 * Internal errors. Means some invariants expected by underlying System has
 * been broken. If you see one of these errors, Something is very broken.
 */
class InternalStatusError extends StatusError {
  grpcType: string = 'Internal';
  code: number = 13;
}

/**
 * The service is currently unavailable. This is a most likely a transient
 * condition and may be corrected by retrying with a backoff. Note that it is
 * not always safe to retry non-idempotent operations.
 *
 * \warning Although data MIGHT not have been transmitted when this
 * status occurs, there is NOT A GUARANTEE that the server has not seen
 * anything. So in general it is unsafe to retry on this status code
 * if the call is non-idempotent.
 *
 * See litmus test above for deciding between FAILED_PRECONDITION, ABORTED,
 * and UNAVAILABLE.
 */
class UnavailableStatusError extends StatusError {
  grpcType: string = 'Unavailable';
  code: number = 14;
}

/**
 * Unrecoverable data loss or corruption.
 */
class DataLossStatusError extends StatusError {
  grpcType: string = 'DataLoss';
  code: number = 15;
}

function translateError<TError extends unknown>(
  err: TError,
):
  | UnknownError
  | DeadlineExceededError
  | ChannelConnectionFailedError
  | NoStatusSentError
  | RequestSendFailedError
  | TError {
  if (
    err instanceof Error &&
    (err as any).errorType &&
    typeof (err as any).errorType === 'string'
  ) {
    let error: Error;

    // Change the error into the right type
    switch ((err as any).errorType as string) {
      case 'DeadlineExceededError':
        error = new DeadlineExceededError();
        break;
      case 'ChannelConnectionFailedError':
        error = new ChannelConnectionFailedError();
        break;
      case 'RequestSendFailedError':
        error = new RequestSendFailedError();
        break;
      case 'NoStatusSentError':
        error = new NoStatusSentError();
        break;
      case 'UnknownError':
        error = new UnknownError();
        break;
      case 'StatusError':
        error = translateStatusError((err as any).code);
        break;
      default:
        error = err;
        break;
    }

    // Update the error message so it corresponds with the original
    error.message = err.message;

    return error;
  }

  return err;
}

const statusCodeErrorMap = {
  1: CancelledStatusError,
  2: UnknownStatusError,
  3: InvalidArgumentStatusError,
  4: DeadlineExceededStatusError,
  5: NotFoundStatusError,
  6: AlreadyExistsStatusError,
  7: PermissionDeniedStatusError,
  8: ResourceExhaustedStatusError,
  9: FailedPreconditionStatusError,
  10: AbortedStatusError,
  11: OutOfRangeStatusError,
  12: UnimplementedStatusError,
  13: InternalStatusError,
  14: UnavailableStatusError,
  15: DataLossStatusError,
  16: UnauthenticatedStatusError,
};

type StatusCodeErrorMap = typeof statusCodeErrorMap;
type StatusCode = keyof StatusCodeErrorMap;

function translateStatusError(status: StatusCode) {
  const ErrorConstructor = statusCodeErrorMap[status];
  if (!ErrorConstructor) {
    const statusError = new StatusError();
    statusError.code = status;
    return statusError;
  }

  return new ErrorConstructor();
}

async function makeUnaryCall(
  clientHandle: number,
  methodName: string,
  request: Uint8Array,
): Promise<Uint8Array> {
  try {
    const resBuffer = await GrpcReactNative.makeUnaryCall(
      clientHandle,
      methodName,
      request.buffer,
    );

    return new Uint8Array(resBuffer);
  } catch (err) {
    throw translateError(err);
  }
}

class Client {
  private readonly handle: number;

  constructor(private readonly channel: Channel) {
    this.handle = GrpcReactNative.createClient(channel.handle);
  }

  public async getProductFromBarcode(
    request: GetProductFromBarcodeRequest,
  ): Promise<GetProductFromBarcodeResponse> {
    return GetProductFromBarcodeResponse.deserializeBinary(
      await this._makeUnaryCall(
        '/stylekorean.StyleKoreanSerice/GetProductFromBarcode',
        request.serializeBinary(),
      ),
    );
  }

  // Makes a unary call to the specified method with this client
  protected _makeUnaryCall(methodName: string, request: Uint8Array) {
    return makeUnaryCall(this.handle, methodName, request);
  }
}

// Define gRPC client with insecure channel
const channel = Channel.createInsecure('192.168.1.187:3200');
const client = new Client(channel);

const App = () => {
  const [isLoading, setIsLoading] = useState(false);

  const onSayHello = async () => {
    setIsLoading(true);

    try {
      const req = new GetProductFromBarcodeRequest();
      req.setBarcode('8809626560095');

      const res = await client.getProductFromBarcode(req);
      console.log('Success!');
      Alert.alert('Product found!', res.getProduct()?.getSalesname());
    } catch (err) {
      if (err instanceof Error) {
        let errorMsg: string;
        if (err instanceof StatusError) {
          errorMsg = ` ${err.grpcType}: ${err.message}`;
        } else {
          errorMsg = `${err.name}: ${err.message}`;
        }
        Alert.alert('Error occured', errorMsg);
      } else {
        Alert.alert('Error occured', 'unknown error');
      }
    }

    setIsLoading(false);
  };

  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView style={styles.safeArea}>
        <View style={styles.inner}>
          <Text style={styles.title}>gRPC Example</Text>
          <Text style={styles.text}>
            Try it out by calling the Greeter service below
          </Text>
          <TouchableOpacity onPress={onSayHello} disabled={isLoading}>
            <View
              style={[
                styles.btnContainer,
                isLoading ? styles.btnContainerDisabled : {},
              ]}>
              <Text
                style={[
                  styles.btnText,
                  isLoading ? styles.btnTextDisabled : {},
                ]}>
                Say Hello!
              </Text>
            </View>
          </TouchableOpacity>
          <ActivityIndicator
            color={'#666'}
            animating={isLoading}
            size={'large'}
            style={{marginTop: 30}}
          />
        </View>
      </SafeAreaView>
    </>
  );
};

const styles = StyleSheet.create({
  safeArea: {
    backgroundColor: 'white',
    flex: 1,
  },
  inner: {
    padding: 30,
  },
  title: {
    fontSize: 40,
    fontWeight: '700',
    marginBottom: 20,
  },
  text: {
    fontSize: 16,
    marginBottom: 20,
  },
  btnContainer: {
    padding: 10,
    borderRadius: 18,
    backgroundColor: '#379c9c',
    alignItems: 'center',
  },
  btnContainerDisabled: {
    backgroundColor: '#ddd',
  },
  btnText: {
    fontWeight: '600',
    color: 'white',
  },
  btnTextDisabled: {
    color: '#aaa',
  },
});

export default App;
