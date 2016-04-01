// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_EXCEPTION_H
#define BXJSONTOOLS_EXCEPTION_H

// Standard library:
#include <string>
#include <exception>

// - Jsoncpp:
#include <json/json.h>

namespace jsontools {

  /// \brief Basic exception
  class exception : public std::exception
  {
  public:

    /// Constructor
    exception(const std::string & error_);

    /// Return the embedded error message
    const char * what() const noexcept;

  private:

    std::string _error_; ///< Embedded error message

  };

  /// \brief Wrong type exception
  class wrong_type : public exception
  {
  public:

    /// Default constructor
    wrong_type();

    /// Constructor
    wrong_type(const Json::Value & _value, const std::string & _str);

    /// Return the embedded JSON value
    Json::Value const & get_value() const;

  private:

    Json::Value _value_; ///< Embedded JSON value

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_EXCEPTION_H
