// -*- mode: c++; -*-

#ifndef JSONTOOLS_BOOST_TYPE_CONVERTERS_H
#define JSONTOOLS_BOOST_TYPE_CONVERTERS_H

// This project:
#include <json/json.h>
#include <jsontools/exception.h>
#include <jsontools/core.h>
#include <jsontools/node.h>

// Boost:
#include <boost/optional.hpp>

namespace jsontools {

  /// A JSON converter dedicated to the boost::optional class
  template<typename T>
  class converter<boost::optional<T>>
  {
  public:

    static void serialize(node & node_, boost::optional<T> & opt_)
    {
      bool init_flag = opt_.is_initialized();
      {
        Json::Value & initValue = node_.grab_value()["initialized"];
        node_value newNode(initValue, node_.is_serializing(), false);
        newNode % init_flag;
      }
      if (init_flag) {
        Json::Value & valueValue = node_.grab_value()["value"];
        node_value newNode(valueValue, node_.is_serializing(), false);
        newNode % opt_.get();
      }
      return;
    }

    static void deserialize(node & node_, boost::optional<T> & opt_)
    {
      bool init_flag = false;
      if (not node_.get_value().isObject()) {
        throw wrong_type(node_.get_value(), "expected object!");
      }
      {
        Json::Value & initValue = node_.grab_value()["initialized"];
        node_value newNode(initValue, node_.is_serializing(), false);
        newNode % init_flag;
      }
      if (init_flag) {
        Json::Value & valueValue = node_.grab_value()["value"];
        node_value newNode(valueValue, node_.is_serializing(), false);
        T value;
        newNode % value;
        opt_ = value;
      }
      return;
    }

  };

} // end of namespace jsontools

#endif // JSONTOOLS_BOOST_TYPE_CONVERTERS_H
