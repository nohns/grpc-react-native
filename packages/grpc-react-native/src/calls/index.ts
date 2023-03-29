import { StatusCode, statusCodeErrorMap } from '../errors/maps';
import {
  ChannelConnectionFailedError,
  DeadlineExceededError,
  NoStatusSentError,
  RequestSendFailedError,
  UnknownError,
} from '../errors/standard';
import { StatusError } from '../errors/status';

export function translateStatusError(status: StatusCode) {
  const ErrorConstructor = statusCodeErrorMap[status];
  if (!ErrorConstructor) {
    const statusError = new StatusError();
    statusError.code = status;
    return statusError;
  }

  return new ErrorConstructor();
}

export function translateError<TError extends unknown>(
  err: TError
): Error | TError {
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
