// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_I_JSONIZABLE_H
#define BXJSONTOOLS_I_JSONIZABLE_H

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
    virtual void jsonize(jsontools::node & node_,
                         const unsigned long int version_ = 0) = 0;

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_I_JSONIZABLE_H
