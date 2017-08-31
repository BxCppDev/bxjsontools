// -*- mode: c++; -*-

#ifndef BXJSONTOOLS_I_JSONIZABLE_H
#define BXJSONTOOLS_I_JSONIZABLE_H

// Standard library:
#include <type_traits>

// This project:
#include <jsontools/core.h>

namespace jsontools {

  class node;

  /// \brief Abstract interface for JSON serializable class
  class i_jsonizable
  {
  public:

    /// Default constructor
    i_jsonizable();

    /// Destructor
    virtual ~i_jsonizable();

    /// Main JSON (de-)serialization method
    virtual void jsonize(jsontools::node & node_,
                         const unsigned long int version_ = 0) = 0;

  };

  /// \brief Specialized template converter for JSON-izable objects
  template<typename T>
  class converter<T, typename std::enable_if<std::is_base_of<::jsontools::i_jsonizable, T>::value>::type>
  {
  public:

    static void jsonize(node & node_, T & x_)
    {
      x_.jsonize(node_, 0);
      return;
    }

    static void dejsonize(node & node_, T & x_)
    {
      x_.jsonize(node_, 0);
      // _dejsonize(node_, x_, 0);
      return;
    }

  };

} // end of namespace jsontools

#endif // BXJSONTOOLS_I_JSONIZABLE_H
