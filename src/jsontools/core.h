// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_CORE_H
#define BXJSONTOOLS_CORE_H

namespace jsontools {

  // template<typename ... Types>
  template<typename T, typename T2 = void, typename ... Types>
  class converter;

  // template<typename ... Types>
  // template<typename T, typename T2 = void, typename ... Types>
  // class converter_split;

} // end of namespace jsontools

#endif // BXJSONTOOLS_CORE_H
