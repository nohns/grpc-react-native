//
//  grpc-rn-exceptions.h
//  grpc-react-native
//
//  Created by Asger Nohns on 27/10/2021.
//

#ifndef grpc_rn_exceptions_h
#define grpc_rn_exceptions_h

#include <iostream>
#include <exception>
#include "grpcpp.h"

namespace GrpcRN {
namespace Exception {

class GenericException : public std::exception {
public:
    virtual const char* type() {
        return "GenericError";
    }
};

class ChannelConnectionFailedException : public GenericException
{
public:
    virtual const char* type() {
        return "ChannelConnectionFailedError";
    }
    
    virtual const char* what() const throw()
    {
        return "A connection could not be made to the gRPC server through the channel";
    }
};

class DeadlineExceededException : public GenericException
{
public:
    virtual const char* type() {
        return "DeadlineExceededError";
    }
    
    virtual const char* what() const throw()
    {
        return "Deadline exceeded during gRPC call";
    }
};

class RequestSendFailedException : public GenericException
{
public:
    virtual const char* type() {
        return "RequestSendFailedError";
    }
    
    virtual const char* what() const throw()
    {
        return "The gRPC request could not be sent";
    }
};

class NoStatusSentException : public GenericException
{
public:
    virtual const char* type() {
        return "NoStatusSentError";
    }
    
    virtual const char* what() const throw()
    {
        return "A status was not sent in the gRPC call answer";
    }
};

class UnknownException : public GenericException
{
public:
    virtual const char* type() {
        return "UnknownError";
    }
    
    virtual const char* what() const throw()
    {
        return "An unknown error occured while trying to call gRPC service";
    }
};

}
}


#endif /* grpc_rn_exceptions_h */
