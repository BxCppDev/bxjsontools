// -*- mode: c++; -*-

// This project:
#include <jsontools/exception.h>

namespace jsontools {

  template<typename T>
  void load(const std::string & file_, T & data_)
  {
    Json::Value root;
    node_value node(root, false, false);
    std::ifstream ifs(file_);
    if (ifs.fail()) {
      throw ::jsontools::exception("Opening file '" + file_ + "' failed");
    }
    std::stringstream strStream;
    strStream << ifs.rdbuf();
    Json::Reader reader;
    if (not reader.parse(strStream.str(), root)) {
      throw ::jsontools::exception("Parsing file '" + file_ + "' failed: " + reader.getFormattedErrorMessages());
    }
    try {
      node % data_;
    } catch(const wrong_type & type) {
      reader.pushError(type.get_value(), type.what(), type.get_value());
      throw ::jsontools::exception("Parsing file '" + file_ + "' failed: "+ reader.getFormattedErrorMessages());
    }
    return;
  }

  template<typename T>
  void store(const std::string & file_, const T & data_)
  {
    Json::Value root;
    node_value node(root, true, false);
    node % const_cast<T &>(data_);
    Json::StyledWriter jsonWriter;
    std::string jsonString = jsonWriter.write(root);
    std::ofstream oFile(file_);
    if (oFile.fail()) {
      throw ::jsontools::exception("Opening file '" + file_ + "' failed!");
    }
    oFile << jsonString;
    oFile.close();
    if (oFile.fail()) {
      throw ::jsontools::exception("Writing to file '" + file_ + "' failed!");
    }
    return;
  }

} // end of namespace jsontools
