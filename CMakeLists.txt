# - Top level CMakeLists.txt for jsontools library

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(jsontools)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "${PROJECT_NAME} requires an out-of-source build.")
  message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
  message(STATUS "  CMakeCache.txt")
  message(STATUS "  CMakeFiles")
  message(STATUS "Once these files are removed, create a separate directory")
  message(STATUS "and run CMake from there, pointing it to:")
  message(STATUS "  ${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "in-source build detected")
endif()

# - Versioning
set(Jsontools_VERSION_MAJOR 0)
set(Jsontools_VERSION_MINOR 1)
set(Jsontools_VERSION_PATCH 0)
set(Jsontools_VERSION "${Jsontools_VERSION_MAJOR}.${Jsontools_VERSION_MINOR}.${Jsontools_VERSION_PATCH}")

include_directories(${PROJECT_SOURCE_DIR}/src)

set(Jsontools_HEADERS
  src/json/json-forwards.h
  src/json/json.h
  src/jsontools/core.h
  src/jsontools/exception.h
  src/jsontools/node.h
  src/jsontools/base_type_converters.h
  src/jsontools/std_type_converters.h
  src/jsontools/serdes.h
  src/jsontools/iofile.h
  src/jsontools/testing/test.h
  )

set(Jsontools_PRIVATE_HEADERS
  )

set(Jsontools_SOURCES
  src/jsontools/testing/test.cc
  src/jsontools/exception.cc
  src/jsontools/node.cc
  src/json/jsoncpp.cpp
  )

# - define amalgamation macro for Jsoncpp
add_definitions(-std=c++11)

add_library(jsontools SHARED
  ${Jsontools_HEADERS}
  ${Jsontools_PRIVATE_HEADERS}
  ${Jsontools_SOURCES}
  )

install( FILES
         ${PROJECT_BINARY_DIR}/libjsontools${CMAKE_SHARED_LIBRARY_SUFFIX}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
         PERMISSIONS OWNER_READ OWNER_EXECUTE
         GROUP_READ GROUP_EXECUTE
         WORLD_READ WORLD_EXECUTE
       )

add_executable(test_jsontools_0 src/jsontools/testing/test_jsontools_0.cxx)

target_link_libraries(test_jsontools_0 jsontools)

# - end of CMakeLists.txt
