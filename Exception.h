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

#endif
