#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
class FileReadException : public std::runtime_error {
public:
  FileReadException();
};

class StateTypeException : public std::runtime_error {
public:
  StateTypeException();
};

class InvalidSyntax : public std::runtime_error {
public:
  InvalidSyntax();
};


#endif
