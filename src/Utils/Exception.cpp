#include "Exception.h"
#include <stdexcept>

  FileReadException::FileReadException() : std::runtime_error("File has incomplete line"){};


  StateTypeException::StateTypeException() : std::runtime_error("Not a valid state"){};

  InvalidSyntax::InvalidSyntax() : std::runtime_error("Invalid syntax error"){};

  InvalidTerminalName::InvalidTerminalName() : std::runtime_error("Invalid teminal name given in the grammar"){};
