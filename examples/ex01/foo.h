// -*- mode: c++; -*-

#ifndef JSONTOOLS_EX01_FOO_H
#define JSONTOOLS_EX01_FOO_H

// Standard library:
#include <iostream>
#include <string>

// Bayeux/jsontools:
#include <jsontools/i_jsonizable.h>

namespace jsontools_ex01 {

  /// \brief A dummy class
  class foo : public jsontools::i_jsonizable
  {
  public:

    /// Constructor
    foo();

    /// Destructor
    virtual ~foo();

    /// Set attributes
    void set(int16_t, uint32_t, double);

    /// Reset attributes
    void reset();

    /// Smart print
    void print(std::ostream & out_, const std::string & indent_ = "") const;

    /// Main JSON (de-)serialization method
    virtual void serialize(jsontools::node & node_,
                           unsigned long int version_ = 0);

  private:

    int16_t  _i16_;
    uint32_t _u32_;
    double   _f64_;

  };

} // end of namespace jsontools_ex01

#endif // JSONTOOLS_EX01_FOO_H
