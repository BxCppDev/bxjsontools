// -*- mode: c++; -*-

#ifndef JSONTOOLS_EX01_FOO_H
#define JSONTOOLS_EX01_FOO_H

// Standard library:
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

// Boost:
#include <boost/date_time/posix_time/posix_time.hpp>

// Bayeux/jsontools:
#include <jsontools/i_jsonizable.h>

// This project:
#include <bar.h>

namespace jsontools_ex01 {

  /// \brief A dummy enumeration type
  enum baz {
    BZ_INVALID = 0,
    BZ_ONE     = 1,
    BZ_TWO     = 2
  };

  /// \brief A dummy class
  class foo
    : public jsontools::i_jsonizable
  {
  public:

    /// Constructor
    foo();

    /// Destructor
    virtual ~foo();

    /// Set attributes
    void set(const bool, const int16_t, const uint32_t, const double, const std::string &);

    /// Append buf
    void append_buf(const uint8_t c_);

    /// Append sequence
    void append_seq(const bar & b_);

    /// Append bar
    void append_bar(const std::string & name_, const bar & b_);

    /// Set timestamp
    void set_timestamp(const boost::posix_time::ptime &);

    /// Set bz
    void set_bz(const baz &);

    /// Reset attributes
    void reset();

    /// Smart print
    void print(std::ostream & out_, const std::string & indent_ = "") const;

    /// Main JSON (de-)serialization method
    virtual void jsonize(jsontools::node & node_,
                         const unsigned long int version_ = 0);

  private:

    bool     _b_;
    int16_t  _i16_;
    uint32_t _u32_;
    double   _f64_;
    std::string _str_;
    std::vector<uint8_t> _buf_;
    std::list<bar> _seq_;
    std::map<std::string, bar> _bars_;
    boost::posix_time::ptime _timestamp_;
    baz _bz_;

  };

} // end of namespace jsontools_ex01

#endif // JSONTOOLS_EX01_FOO_H
