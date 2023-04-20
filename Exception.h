#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
class FileReadException : public std::runtime_error {
public:
  FileReadException() : std::runtime_error("File has incomplete line"){};
};

#endif
