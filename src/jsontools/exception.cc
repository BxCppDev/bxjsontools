// Ourselves:
#include <jsontools/exception.h>

namespace jsontools {

  exception::exception(const std::string & error_)
    : _error_(error_)
  {
    return;
  }

  const char * exception::what() const noexcept
  {
    return _error_.c_str();
  }

  wrong_type::wrong_type() : exception("expected different type")
  {
    return;
  }

  wrong_type::wrong_type(const Json::Value & value_,
                         const std::string & str_)
      : exception(str_), _value_(value_)
  {
    return;
  }

  const Json::Value & wrong_type::get_value() const
  {
    return _value_;
  }

} // end of namespace jsontools
