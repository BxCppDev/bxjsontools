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

    static void serialize(node & node_, T & x_)
    {
      x_.serialize(node_, 0);
      return;
    }

    static void deserialize(node & node_, T & x_)
    {
      _deserialize(node_, x_, 0);
      return;
    }

  };

  template<typename T>
  auto _deserialize(node & node_, T & x_, int)
    -> decltype(x_.deserialize(node_, 0))
  {
    x_.deserialize(node_, 0);
    return;
  }

  template<typename T>
  auto _deserialize(node & node_, T & x_, long)
    -> decltype(x_.serialize(node_, 0))
  {
    x_.serialize(node_, 0);
    return;
  }

} // end of namespace jsontools

#endif // BXJSONTOOLS_SERDES_H
