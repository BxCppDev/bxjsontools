// Ourselves:
#include "node.h"

namespace jsontools {

  node::node(Json::Value & value_, bool serializing_)
    : _value(value_) , _serializing(serializing_)
  {
    return;
  }

  node_value node::operator[](const std::string & s_)
  {
    bool defaultValueNeeded = not _value.isMember(s_);
    return node_value(_value[s_], _serializing, defaultValueNeeded);
  }

  bool node::is_serializing() const
  {
    return _serializing;
  }

  const Json::Value & node::get_value() const
  {
    return _value;
  }

  Json::Value & node::grab_value()
  {
    return _value;
  }

  node_value::node_value(Json::Value & value_,
                         bool serializing_,
                         bool default_value_needed_)
    : node(value_, serializing_), _default_value_needed_(default_value_needed_)
  {
    return;
  }

} // end of namespace jsontools
