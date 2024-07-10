//
// Created by patryk on 6/11/24.
//

#ifndef BASEERROR_H
#define BASEERROR_H
#include <stdexcept>


class BaseError : public std::logic_error {
public:
    explicit BaseError(const std::string &message) : logic_error(message) {}
};

class ObjectNotFoundException : public BaseError {
public:
    explicit ObjectNotFoundException(const std::string &message) : BaseError(message) {}
};

class DuplicateException : public BaseError {
public:
    explicit DuplicateException(const std::string &message) : BaseError(message) {}
};

class BadRequestException : public BaseError {
public:
    explicit BadRequestException(const std::string &message) : BaseError(message) {}
};





#endif //BASEERROR_H
