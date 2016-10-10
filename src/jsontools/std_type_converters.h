// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_STD_TYPE_CONVERTERS_H
#define BXJSONTOOLS_STD_TYPE_CONVERTERS_H

// Standard library:
#include <string>
#include <vector>
#include <list>
#include <array>
#include <map>

// This project:
#include <json/json.h>
#include <jsontools/exception.h>
#include <jsontools/core.h>
#include <jsontools/node.h>

namespace jsontools {

  template<>
  class converter<std::string>
  {
  public:

    static void jsonize(node & node_, std::string & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void dejsonize(node & node_, std::string & x_)
    {
      if (not node_.get_value().isString()) {
        throw wrong_type(node_.get_value(), "expected string");
      }
      x_ = node_.get_value().asString();
      return;
    }

  };

  template<typename T>
  class converter<std::vector<T>>
  {
  public:

    static void jsonize(node & node_, std::vector<T> & x_)
    {
      node_.grab_value() = Json::arrayValue;
      for (auto & e : x_) {
        Json::Value value;
        node_value newNode(value, node_.is_serializing(), false);
        newNode % e;
        node_.grab_value().append(value);
      }
      return;
    }

    static void dejsonize(node & node_, std::vector<T> & x_)
    {
      if (not node_.get_value().isArray()) {
        throw wrong_type(node_.get_value(), "expected array");
      }
      x_.clear();
      x_.reserve(node_.get_value().size());
      for (uint i(0); i < node_.get_value().size(); ++i) {
        x_.push_back(T());
        node_value newNode(node_.grab_value()[i],
                           node_.is_serializing(),
                           false);
        newNode % x_.back();
      }
      return;
    }

  };

  template<typename T>
  class converter<std::list<T>>
  {
  public:

    static void jsonize(node & node_, std::list<T> & x_)
    {
      node_.grab_value() = Json::arrayValue;
      for (auto e : x_) {
        Json::Value value;
        node_value newNode(value, node_.is_serializing(), false);
        newNode % e;
        node_.grab_value().append(value);
      }
      return;
    }

    static void dejsonize(node & node_, std::list<T> & x_)
    {
      if (not node_.get_value().isArray()) {
        throw wrong_type(node_.get_value(), "expected array");
      }
      x_.clear();
      for (uint i(0); i < node_.get_value().size(); ++i) {
        x_.push_back(T());
        node_value newNode(node_.grab_value()[i],
                           node_.is_serializing(),
                           false);
        newNode % x_.back();
      }
      return;
    }

  };

  template<typename T, std::size_t N>
  class converter<std::array<T, N>>
  {
  public:

    static void jsonize(node & node_, std::array<T, N> & x_)
    {
      node_.grab_value() = Json::arrayValue;
      for (auto & e : x_) {
        Json::Value value;
        node_value newNode(value, node_.is_serializing(), false);
        newNode % e;
        node_.grab_value().append(value);
      }
      return;
    }

    static void dejsonize(node & node_, std::array<T, N> & x_)
    {
      if (not node_.get_value().isArray()) {
        throw wrong_type(node_.get_value(), "expected array");
      }
      for (uint i(0); i < node_.get_value().size(); ++i) {
        node_value newNode(node_.grab_value()[i],
                           node_.is_serializing(),
                           false);
        newNode % x_[i];
      }
      return;
    }

  };


  template<typename T1, typename T2>
  class converter<std::map<T1, T2>>
  {
  public:

    static void jsonize(node & node_, std::map<T1, T2> & x_)
    {
      node_.grab_value() = Json::arrayValue;
      for (auto & e : x_) {
        T1   key   = e.first;
        T2 & value = e.second;
        Json::Value jsonValue;
        node_value(jsonValue["key"], true, false)   % key;
        node_value(jsonValue["value"], true, false) % value;
        node_.grab_value().append(jsonValue);
      }
      return;
    }

    static void dejsonize(node & node_, std::map<T1, T2> & x_)
    {
      if (not node_.get_value().isArray()) {
        throw wrong_type(node_.get_value(), "expected array");
      }
      x_.clear();
      for (uint i(0); i < node_.get_value().size(); ++i) {
        T1 key;
        T2 value;
        node_value(node_.grab_value()[i]["key"], false, false)   % key;
        node_value(node_.grab_value()[i]["value"], false, false) % value;
        x_[key] = std::move(value);
      }
      return;
    }

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_STD_TYPE_CONVERTERS_H
