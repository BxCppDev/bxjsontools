// -*- mode: c++; -*-

#ifndef JSONTOOLS_I_JSONIZABLE_H
#define JSONTOOLS_I_JSONIZABLE_H

// This project:
#include <jsontools/node.h>
#include <jsontools/serdes.h>

namespace jsontools {

  /// \brief Abstract interface for JSON serializable class
  class i_jsonizable
  {
  public:

    /// Default constructor
    i_jsonizable();

    /// Destructor
    virtual ~i_jsonizable();

    /// Main JSON (de-)serialization method
    virtual void serialize(jsontools::node & node_,
                           unsigned long int version_ = 0) = 0;

  };

} // end of namespace jsontools

#endif // JSONTOOLS_I_JSONIZABLE_H
