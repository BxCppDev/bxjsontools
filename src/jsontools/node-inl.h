// -*- mode: c++; -*-

// This project:
#include <jsontools/core.h>

namespace jsontools {

  template<typename T>
  node_value_default<T> node_value::operator%(T & x_)
  {
    if (_serializing) {
      converter<T>::jsonize(*this, x_);
      _default_value_needed_ = false;
    } else if (not _default_value_needed_) {
      converter<T>::dejsonize(*this, x_);
    }
    return node_value_default<T>(x_, _default_value_needed_);
  }

  template<typename T>
  node_value_default<T>::node_value_default(T & t_,
                                            bool need_default_value_)
    : _t_(t_)
    , _need_default_value_(need_default_value_)
  {
    return;
  }

  template<typename T>
  void node_value_default<T>::operator or(const T & t_)
  {
    if (_need_default_value_) {
      _t_ = t_;
      _need_default_value_ = false;
    }
    return;
  }

} // end of namespace jsontools
