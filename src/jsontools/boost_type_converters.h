// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_BOOST_TYPE_CONVERTERS_H
#define BXJSONTOOLS_BOOST_TYPE_CONVERTERS_H

// Standard library:
#include <string>

// This project:
#include <json/json.h>
#include <jsontools/exception.h>
#include <jsontools/core.h>
#include <jsontools/node.h>

// Boost:
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace jsontools {

  /// A JSON converter dedicated to the boost::optional class
  template<typename T>
  class converter<boost::optional<T>>
  {
  public:

    static void jsonize(node & node_, boost::optional<T> & opt_)
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

    static void dejsonize(node & node_, boost::optional<T> & opt_)
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

  /// A JSON converter dedicated to the boost::posix_time::ptime class
  template<>
  class converter<boost::posix_time::ptime>
  {
  public:

    static void jsonize(node & node_, boost::posix_time::ptime & t_)
    {
      // if (not node_.get_value().isString()) {
        std::string tstr;
        if (t_.is_neg_infinity()) {
          tstr = "-infinity";
        } else if (t_.is_pos_infinity()) {
          tstr = "+infinity";
        } else if (t_.is_not_a_date_time()) {
          tstr = "not-a-date-time";
        } else {
          tstr = boost::posix_time::to_iso_string(t_);
        }
        node_.grab_value() = tstr;
        //}

      return;
    }

    static void dejsonize(node & node_, boost::posix_time::ptime & t_)
    {
      if (not node_.get_value().isString()) {
        throw wrong_type(node_.get_value(), "expected string");
      }
      std::string tstr = node_.get_value().asString();
      if (tstr == "-infinity") {
        t_ = boost::posix_time::ptime(boost::posix_time::neg_infin);
      } else if (tstr == "+infinity") {
        t_ = boost::posix_time::ptime(boost::posix_time::pos_infin);
      } else if (tstr == "not-a-date-time") {
        t_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
      } else {
        t_ = boost::posix_time::from_iso_string(tstr);
      }
      return;
    }

  };

  /// A JSON converter dedicated to the boost::posix_time::time_period class
  template<>
  class converter<boost::posix_time::time_period>
  {
  public:

    static void jsonize(node & node_, boost::posix_time::time_period & tp_)
    {
      boost::posix_time::ptime b = tp_.begin();
      boost::posix_time::ptime e = tp_.end();
      {
        Json::Value & beginValue = node_.grab_value()["begin"];
        node_value newNode(beginValue, node_.is_serializing(), false);
        newNode % b;
      }
      {
        Json::Value & endValue = node_.grab_value()["end"];
        node_value newNode(endValue, node_.is_serializing(), false);
        newNode % e;
      }
      return;
    }

    static void dejsonize(node & node_, boost::posix_time::time_period & t_)
    {
      if (not node_.get_value().isObject()) {
        throw wrong_type(node_.get_value(), "expected object");
      }
      boost::posix_time::ptime b, e;
      {
        Json::Value & beginValue = node_.grab_value()["begin"];
        node_value newNode(beginValue, node_.is_serializing(), false);
        newNode % b;
      }
      {
        Json::Value & endValue = node_.grab_value()["end"];
        node_value newNode(endValue, node_.is_serializing(), false);
        newNode % e;
      }
      t_ = boost::posix_time::time_period(b, e);
      return;
    }

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_BOOST_TYPE_CONVERTERS_H
