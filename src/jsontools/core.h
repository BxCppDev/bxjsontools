// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_CORE_H
#define BXJSONTOOLS_CORE_H

namespace jsontools {

  // template<typename ...T>
  template <typename T, typename T2 = void, typename Enable = void>
  class converter;

  // template<typename ...T>
  // class converter_split;

} // end of namespace jsontools

#endif // BXJSONTOOLS_CORE_H
