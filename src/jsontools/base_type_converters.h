// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_BASE_TYPE_CONVERTERS_H
#define BXJSONTOOLS_BASE_TYPE_CONVERTERS_H

// This project:
#include <json/json.h>
#include <jsontools/exception.h>
#include <jsontools/core.h>
#include <jsontools/node.h>

namespace jsontools {

  template<>
  class converter<bool>
  {
  public:

    static void serialize(node & node_, bool & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void deserialize(node & node_, bool & x_)
    {
      if (not node_.get_value().isBool()) {
        throw wrong_type(node_.get_value(), "expected bool");
      }
      x_ = node_.get_value().asBool();
      return;
    }

  };


  template<>
  class converter<uint8_t>
  {
  public:

    static void serialize(node & node, uint8_t & x_)
    {
      node.grab_value() = x_;
      return;
    }

    static void deserialize(node & node, uint8_t & x_)
    {
      if (not node.get_value().isUInt()) {
        throw wrong_type(node.get_value(), "expected uint8_t");
      }
      uint32_t t = node.get_value().asUInt();
      if (t > (1<<8)-1) {
        throw wrong_type(node.get_value(), "expected uint8_t");
      }
      x_ = t;
      return;
    }

  };

  template<>
  class converter<int8_t>
  {
  public:

    static void serialize(node & node, int8_t & x_)
    {
      node.grab_value() = x_;
      return;
    }

    static void deserialize(node & node, int8_t & x_)
    {
      if (not node.get_value().isInt()) {
        throw wrong_type(node.get_value(), "expected int8_t");
      }
      int32_t t = node.get_value().asInt();
      if (t > (1<<7)-1 || t < -128) {
        throw wrong_type(node.get_value(), "expected int8_t");
      }
      x_ = t;
      return;
    }

  };

  template<>
  class converter<uint16_t>
  {
  public:

    static void serialize(node & node, uint16_t & x_)
    {
      node.grab_value() = x_;
      return;
    }

    static void deserialize(node & node, uint16_t & x_)
    {
      if (not node.get_value().isUInt()) {
        throw wrong_type(node.get_value(), "expected uint16_t");
      }
      uint32_t t = node.get_value().asUInt();
      if (t > (1<<16)-1) {
        throw wrong_type(node.get_value(), "expected uint16_t");
      }
      x_ = t;
      return;
    }

  };

  template<>
  class converter<int16_t>
  {
  public:

    static void serialize(node & node_, int16_t & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void deserialize(node & node_, int16_t & x_)
    {
      if (not node_.get_value().isInt()) {
        throw wrong_type(node_.get_value(), "expected int16_t");
      }
      int32_t t = node_.get_value().asInt();
      if (t > (1<<15)-1 || t < -32768 ) {
        throw wrong_type(node_.get_value(), "expected int16_t");
      }
      x_ = t;
      return;
    }

  };

  template<>
  class converter<uint32_t>
  {
  public:

    static void serialize(node & node_, uint32_t & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void deserialize(node & node_, uint32_t & x_)
    {
      if (not node_.get_value().isUInt()) {
        throw wrong_type(node_.get_value(), "expected uint32_t");
      }
      x_ = node_.get_value().asUInt();
      return;
    }

  };

  template<>
  class converter<int32_t> {
  public:

    static void serialize(node & node_, int32_t & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void deserialize(node & node_, int32_t & x_)
    {
      if (not node_.get_value().isInt()) {
        throw wrong_type(node_.get_value(), "expected int32_t");
      }
      x_ = node_.get_value().asInt();
      return;
    }

  };

  template<>
  class converter<float>
  {
  public:

    static void serialize(node & node_, float & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void deserialize(node & node_, float & x_)
    {
      if (not node_.get_value().isDouble()) {
        throw wrong_type(node_.get_value(), "expected float");
      }
      x_ = node_.get_value().asFloat();
      return;
    }

  };

  template<>
  class converter<double>
  {
  public:

    static void serialize(node & node_, double & x_)
    {
      node_.grab_value() = x_;
      return;
    }

    static void deserialize(node & node_, double & x_)
    {
      if (not node_.get_value().isDouble()) {
        throw wrong_type(node_.get_value(), "expected double");
      }
      x_ = node_.get_value().asDouble();
      return;
    }

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_BASE_TYPE_CONVERTERS_H
