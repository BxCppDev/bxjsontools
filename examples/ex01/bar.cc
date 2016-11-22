// Ourselves:
#include <bar.h>

// - Bayeux/jsontools:
#include <jsontools/base_type_converters.h>
#include <jsontools/std_type_converters.h>

namespace jsontools_ex01 {

  bar::bar()
  {
    return;
  }

  bar::bar(const int32_t value_, const std::string & label_)
    : value(value_)
    , label(label_)
  {
    return;
  }

  bar::~bar()
  {
  }

  void bar::jsonize(jsontools::node & node_,
                    const unsigned long int /* version_ */)
  {
    node_["value"] % value;
    node_["label"] % label;
    return;
  }

} // end of namespace jsontools_ex01
