// -*- mode: c++; -*-

#ifndef JSONTOOLS_EX01_BAR_H
#define JSONTOOLS_EX01_BAR_H

// Standard library:
#include <string>

// Bayeux/jsontools:
#include <jsontools/i_jsonizable.h>

namespace jsontools_ex01 {

  /// \brief A simple record
  struct bar : public jsontools::i_jsonizable
  {
    bar() {
      return;
    }

    bar(int32_t value_, const std::string & label_)
      : value(value_), label(label_) {
      return;
    }

    /// Main JSON (de-)serialization method
    virtual void jsonize(jsontools::node & node_,
                         unsigned long int version_ = 0);

    int32_t     value = 0;
    std::string label;
  };

} // end of namespace jsontools_ex01

#endif // JSONTOOLS_EX01_BAR_H
