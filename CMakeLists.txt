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

option(BAYEUX_ENABLE_TESTING "Build unit testing system for Bayeux/jsontools" ON)
if(BAYEUX_ENABLE_TESTING)
  enable_testing()
endif()

set(jsontools_TESTS
  src/jsontools/testing/test_jsontools_0.cxx
  )

if(BAYEUX_ENABLE_TESTING)
  foreach(_testsource ${jsontools_TESTS})
    set(_jsontools_TEST_ENVIRONMENT
      # "BXJSONTOOLS_RESOURCE_FILES_DIR=${PROJECT_SOURCE_DIR}/resources"
      )
    get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "jsontools-${_testname}")
    add_executable(${_testname} ${_testsource})
    target_link_libraries(${_testname} jsontools)
    # - On Apple, ensure dynamic_lookup of undefined symbols
    if(APPLE)
      set_target_properties(${_testname} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif()
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_property(TEST ${_testname}
      APPEND PROPERTY ENVIRONMENT ${_jsontools_TEST_ENVIRONMENT}
      )
    # - For now, dump them into the testing output directory
    set_target_properties(${_testname}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxjsontools_tests
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxjsontools_tests
      )
  endforeach()
endif()

# - end of CMakeLists.txt
