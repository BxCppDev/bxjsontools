// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_NODE_H
#define BXJSONTOOLS_NODE_H

// This project:
#include <json/json.h>
#include <jsontools/core.h>

namespace jsontools {

  class node_value;

  template<typename T>
  class node_value_default;

  /// \brief JSON value accessor node
  class node
  {
  public:

    /// Constructor
    node(Json::Value & value_, bool serializing_);

    /// Check serialization flag
    bool is_serializing() const;

    /// Return the embedded JSON value
    const Json::Value & get_value() const;

    /// Return the embedded JSON value
    Json::Value & grab_value();

    /// Access to a node value item with given name
    node_value operator[](const std::string & s_);

  protected:

    Json::Value & _value;       ///< Embedded JSON value
    bool          _serializing; ///< Serialize flag

  };

  /// \brief Node value
  class node_value
    : public node
  {
  public:

    /// Constructor
    node_value(Json::Value & value_,
               bool serializing_,
               bool default_value_needed_);

    template<typename T>
    node_value_default<T> operator%(T & x_);

  private:

    bool _default_value_needed_; ///< Flag for needed default value

  };

  /// \brief
  template<typename T>
  class node_value_default
  {
  public:

    /// Constructor
    node_value_default(T & t_, bool need_default_value_);

    /// Or operator
    void operator or(const T & t_);

  private:

    T &  _t_;                  ///< Reference to a default value
    bool _need_default_value_; ///< Flag set if a default value is needed

  };

} // end of namespace jsontools

#include "node-inl.h"

#endif // BXJSONTOOLS_NODE_H
