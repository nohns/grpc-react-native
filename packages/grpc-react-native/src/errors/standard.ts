export class UnknownError extends Error {
  name: string = 'UnknownError';
}

export class DeadlineExceededError extends Error {
  name: string = 'DeadlineExceededError';
}

export class ChannelConnectionFailedError extends Error {
  name: string = 'ChannelConnectionFailedError';
}

export class NoStatusSentError extends Error {
  name: string = 'NoStatusSentError';
}

export class RequestSendFailedError extends Error {
  name: string = 'RequestSendFailedError';
}
