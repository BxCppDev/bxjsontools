// Ourselves:
#include <bar.h>

// - Bayeux/jsontools:
#include <jsontools/base_type_converters.h>
#include <jsontools/std_type_converters.h>

namespace jsontools_ex01 {

  void bar::jsonize(jsontools::node & node_,
                    unsigned long int /* version_ */)
  {
    node_["value"] % value;
    node_["label"] % label;
    return;
  }

} // end of namespace jsontools_ex01
