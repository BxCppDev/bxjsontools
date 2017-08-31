// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_SERDES_H
#define BXJSONTOOLS_SERDES_H

// Standard library:
#include <type_traits>

// This project:
#include <jsontools/core.h>
#include <jsontools/node.h>
#include <jsontools/i_jsonizable.h>

namespace jsontools {

  template<typename T>
  class converter<T> //, typename std::enable_if<std::is_class<T>::value>::type>
  /// \brief Generic converter from object of class T
  ///        to a protobuf message wrapper node.
  ///
  ///        The class T is expected to inherit the
  ///        jsontools::i_jsonizable interface.
  // template<typename T>
  // class converter<T, typename std::enable_if<std::is_base_of<::jsontools::i_jsonizable, T>::value>::type>
  {
  public:

    static void jsonize(node & node_, T & x_)
    {
      x_.jsonize(node_, 0);
      return;
    }

    static void dejsonize(node & node_, T & x_)
    {
      _dejsonize(node_, x_, 0);
      return;
    }

  };

  template<typename T>
  auto _dejsonize(node & node_, T & x_, int)
    -> decltype(x_.dejsonize(node_, 0))
  {
    x_.dejsonize(node_, 0);
    return;
  }

  template<typename T>
  auto _dejsonize(node & node_, T & x_, long)
    -> decltype(x_.jsonize(node_, 0))
  {
    x_.jsonize(node_, 0);
    return;
  }

} // end of namespace jsontools

#endif // BXJSONTOOLS_SERDES_H
