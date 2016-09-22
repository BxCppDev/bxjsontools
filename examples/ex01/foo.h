// -*- mode: c++; -*-

#ifndef JSONTOOLS_EX01_FOO_H
#define JSONTOOLS_EX01_FOO_H

// Standard library:
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

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
    virtual void serialize(jsontools::node & node_,
                           unsigned long int version_ = 0);

    int32_t     value = 0;
    std::string label;
  };

  /// \brief A dummy class
  class foo : public jsontools::i_jsonizable
  {
  public:

    /// Constructor
    foo();

    /// Destructor
    virtual ~foo();

    /// Set attributes
    void set(bool, int16_t, uint32_t, double, const std::string &);

    /// Append buf
    void append_buf(uint8_t c_);

    /// Append sequence
    void append_seq(const bar & b_);

    /// Append bar
    void append_bar(const std::string & name_, const bar & b_);

    /// Reset attributes
    void reset();

    /// Smart print
    void print(std::ostream & out_, const std::string & indent_ = "") const;

    /// Main JSON (de-)serialization method
    virtual void serialize(jsontools::node & node_,
                           unsigned long int version_ = 0);

  private:

    bool     _b_;
    int16_t  _i16_;
    uint32_t _u32_;
    double   _f64_;
    std::string _str_;
    std::vector<uint8_t> _buf_;
    std::list<bar> _seq_;
    std::map<std::string, bar> _bars_;

  };

} // end of namespace jsontools_ex01

#endif // JSONTOOLS_EX01_FOO_H
