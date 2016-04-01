// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_IOFILE_H
#define BXJSONTOOLS_IOFILE_H

// Standard library:
#include <fstream>

// This project:
#include <json/json.h>
#include <jsontools/node.h>

namespace jsontools {

  template<typename T>
  void load(const std::string & file_, T & data_);

  template<typename T>
  void store(const std::string & file_, const T & data_);

} // end of namespace jsontools

#include "iofile-inl.h"

#endif // BXJSONTOOLS_IOFILE_H
