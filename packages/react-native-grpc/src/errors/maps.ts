import {
  CancelledStatusError,
  UnknownStatusError,
  InvalidArgumentStatusError,
  DeadlineExceededStatusError,
  NotFoundStatusError,
  AlreadyExistsStatusError,
  PermissionDeniedStatusError,
  ResourceExhaustedStatusError,
  FailedPreconditionStatusError,
  AbortedStatusError,
  OutOfRangeStatusError,
  UnimplementedStatusError,
  InternalStatusError,
  UnavailableStatusError,
  DataLossStatusError,
  UnauthenticatedStatusError,
} from './status';

export const statusCodeErrorMap = {
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

export type StatusCodeErrorMap = typeof statusCodeErrorMap;
export type StatusCode = keyof StatusCodeErrorMap;
