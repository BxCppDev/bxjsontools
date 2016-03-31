// -*- mode: c++; -*-

#ifndef JSONTOOLS_JSONTOOLS_H
#define JSONTOOLS_JSONTOOLS_H

#include <json/json.h>
#include <json/json-forwards.h>
#include <jsontools/version.h>
#include <jsontools/config.h>
#include <jsontools/core.h>
#include <jsontools/exception.h>
#include <jsontools/node.h>
#include <jsontools/serdes.h>
#include <jsontools/base_type_converters.h>
#include <jsontools/std_type_converters.h>
#include <jsontools/iofile.h>
#if JSONTOOLS_WITH_BOOST == 1
#include <jsontools/boost_type_converters.h>
#endif // JSONTOOLS_WITH_BOOST == 1

#endif // JSONTOOLS_JSONTOOLS_H
