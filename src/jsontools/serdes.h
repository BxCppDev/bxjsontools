// -*- mode: c++; -*-

#ifndef JSONTOOLS_SERDES_H
#define JSONTOOLS_SERDES_H

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
      x_.serialize(node_);
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
    -> decltype(x_.deserialize(node_))
  {
    x_.deserialize(node_);
    return;
  }

  template<typename T>
  auto _deserialize(node & node_, T & x_, long)
    -> decltype(x_.serialize(node_))
  {
    x_.serialize(node_);
    return;
  }

} // end of namespace jsontools

#endif // JSONTOOLS_SERDES_H
