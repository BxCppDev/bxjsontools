// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_IO_H
#define BXJSONTOOLS_IO_H

// Standard library:
#include <iostream>

// This project:
#include <json/json.h>
#include <jsontools/node.h>

namespace jsontools {

  /// Deserialize an object of given type from an input stream
  template<typename T>
  void load(std::istream & in_, T & data_);

  /// Serialize an object of given type to an output stream
  template<typename T>
  void store(std::ostream & out_, const T & data_);

} // end of namespace jsontools

#include "io-inl.h"

#endif // BXJSONTOOLS_IO_H
