#include "Exception.h"
#include <stdexcept>

  FileReadException::FileReadException() : std::runtime_error("File has incomplete line"){};


  StateTypeException::StateTypeException() : std::runtime_error("Not a valid state"){};


