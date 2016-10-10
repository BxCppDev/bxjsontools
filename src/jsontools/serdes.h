// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_SERDES_H
#define BXJSONTOOLS_SERDES_H

// This project:
#include <jsontools/core.h>
#include <jsontools/node.h>

namespace jsontools {

  template<typename T>
  class converter<T>
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
