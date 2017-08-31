// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_ENUM_CONVERTER_H
#define BXJSONTOOLS_ENUM_CONVERTER_H

// Standard library:
#include <type_traits>

// This project:
#include <json/json.h>
#include <jsontools/exception.h>
#include <jsontools/core.h>
#include <jsontools/node.h>

namespace jsontools {

  /// \brief Converter from object of enumeration class T
  ///        to a protobuf message wrapper node.
  ///
  ///        The class T is expected to check std::is_enum<T>::value.
  template<typename T>
  class converter<T, typename std::enable_if<std::is_enum<T>::value>::type>
  {
  public:

    // Generic serialization method for enumeration value
    static void jsonize(node & node_, T & enum_value_)
    {
      int32_t val = static_cast<int32_t>(enum_value_);
      node_.grab_value() = val;
      return;
    }

    // Generic deserialization method for enumeration value
    static void dejsonize(node & node_, T & enum_value_)
    {
      if (not node_.get_value().isInt()) {
        throw wrong_type(node_.get_value(), "expected int32_t");
      }
      int32_t val = node_.get_value().asInt();
      enum_value_ = static_cast<T>(val);
      return;
    }

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_ENUM_CONVERTER_H
