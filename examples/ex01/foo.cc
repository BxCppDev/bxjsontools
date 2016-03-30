// Ourselves:
#include <foo.h>

// - Bayeux/jsontools:
#include <jsontools/base_type_converters.h>

namespace jsontools_ex01 {

  foo::foo()
  {
    _i16_ = 0;
    _u32_ = 0;
    _f64_ = 0.0;
    return;
  }

  foo::~foo()
  {
    return;
  }

  void foo::set(int16_t i_, uint32_t u_, double d_)
  {
    _i16_ = i_;
    _u32_ = u_;
    _f64_ = d_;
    return;
  }

  void foo::reset()
  {
    _i16_ = 0;
    _u32_ = 0;
    _f64_ = 0.0;
    return;
  }

  void foo::print(std::ostream & out_, const std::string & indent_) const
  {
    out_ << indent_ << "|-- i16 : " << _i16_ << '\n';
    out_ << indent_ << "|-- u32 : " << _u32_ << '\n';
    out_ << indent_ << "`-- f64 : " << _f64_ << '\n';
    return;
  }

  void foo::serialize(jsontools::node & node_,
                      unsigned long int /* version_ */)
  {
    node_["i16"] % _i16_;
    node_["u32"] % _u32_;
    node_["f64"] % _f64_;
    return;
  }

} // end of namespace jsontools_ex01
