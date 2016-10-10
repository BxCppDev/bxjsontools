// -*- mode: c++; -*-

// This project:
#include <jsontools/exception.h>

namespace jsontools {

  template<typename T>
  void load(std::istream & in_, T & data_)
  {
    Json::Value root;
    node_value node(root, false, false);
    std::stringstream strStream;
    // FIXME
    strStream << in_.rdbuf();
    Json::Reader reader;
    if (not reader.parse(strStream.str(), root)) {
      throw ::jsontools::exception("JSON parsing failed: " + reader.getFormattedErrorMessages());
    }
    try {
      node % data_;
    } catch(const wrong_type & type) {
      reader.pushError(type.get_value(), type.what(), type.get_value());
      throw ::jsontools::exception("JSON parsing failed: "+ reader.getFormattedErrorMessages());
    }
    return;
  }

  template<typename T>
  void store(std::ostream & out_, const T & data_)
  {
    Json::Value root;
    node_value node(root, true, false);
    node % const_cast<T &>(data_);
    Json::StyledWriter jsonWriter;
    std::string jsonString = jsonWriter.write(root);
    out_ << jsonString;
    return;
  }

} // end of namespace jsontools
