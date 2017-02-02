# - Top level CMakeLists.txt for bxjsontools_ex01 example program

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(bxjsontools_ex01)

message( STATUS "[info] ${PROJECT_NAME}: Entering...")

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

include(GNUInstallDirs)
# - Validate that certain paths are relative, otherwise relocation may fail
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "[fatal] ${PROJECT_NAME}: Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()
message(STATUS "[info] CMAKE_INSTALL_PREFIX           = '${CMAKE_INSTALL_PREFIX}'")
message(STATUS "[info] CMAKE_INSTALL_BINDIR           = '${CMAKE_INSTALL_BINDIR}'")
message(STATUS "[info] CMAKE_INSTALL_LIBDIR           = '${CMAKE_INSTALL_LIBDIR}'")
message(STATUS "[info] CMAKE_INSTALL_INCLUDEDIR       = '${CMAKE_INSTALL_INCLUDEDIR}'")
message(STATUS "[info] CMAKE_INSTALL_DATAROOTDIR      = '${CMAKE_INSTALL_DATAROOTDIR}'")
message(STATUS "[info] CMAKE_INSTALL_FULL_LIBDIR      = '${CMAKE_INSTALL_FULL_LIBDIR}'")
message(STATUS "[info] CMAKE_INSTALL_FULL_BINDIR      = '${CMAKE_INSTALL_FULL_BINDIR}'")
message(STATUS "[info] CMAKE_INSTALL_FULL_INCLUDEDIR  = '${CMAKE_INSTALL_FULL_INCLUDEDIR}'")
message(STATUS "[info] CMAKE_INSTALL_FULL_DATAROOTDIR = '${CMAKE_INSTALL_FULL_DATAROOTDIR}'")

# -- RPATH settings --
# From: https://cmake.org/Wiki/CMake_RPATH_handling
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
endif()

# - Find BxJsontools:
message(STATUS "[info] Searching for BxJsontools version 0.1...")
find_package(BxJsontools 0.1 REQUIRED CONFIG)
message(STATUS "[info] BxJsontools_VERSION          = '${BxJsontools_VERSION}'")
message(STATUS "[info] BxJsontools_DEFINITIONS      = '${BxJsontools_DEFINITIONS}'")
message(STATUS "[info] BxJsontools_INCLUDE_DIRS     = '${BxJsontools_INCLUDE_DIRS}'")
message(STATUS "[info] BxJsontools_LIBRARIES        = '${BxJsontools_LIBRARIES}'")
message(STATUS "[info] BxJsontools_BOOST_VERSION    = '${BxJsontools_BOOST_VERSION}'")
message(STATUS "[info] BxJsontools_BOOST_COMPONENTS = '${BxJsontools_BOOST_COMPONENTS}'")

# - Find Boost:
message(STATUS "[info] Searching for Boost version ${BxJsontools_BOOST_VERSION} with 'MODULE' mode...")
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost ${BxJsontools_BOOST_VERSION} EXACT
  REQUIRED
  ${BxJsontools_BOOST_COMPONENTS}
  )
message(STATUS "[info] Boost_VERSION      = '${Boost_VERSION}'")
message(STATUS "[info] Boost_INCLUDE_DIRS = '${Boost_INCLUDE_DIRS}'")
message(STATUS "[info] Boost_LIBRARIES    = '${Boost_LIBRARIES}'")

set(_incs
  ${BxJsontools_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )
set(_libs
  ${BxJsontools_LIBRARIES}
  ${Boost_LIBRARIES}
  )
add_definitions(${BxJsontools_DEFINITIONS})
include_directories(${PROJECT_SOURCE_DIR} ${_incs})

# - Library:
message(STATUS "[info] Adding library 'Bayeux_jsontools_ex01'...")
add_library(Bayeux_jsontools_ex01 SHARED
  bar.h
  foo.h
  bar.cc
  foo.cc
  )
target_link_libraries(Bayeux_jsontools_ex01 ${_libs} )
install(TARGETS Bayeux_jsontools_ex01
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  )

# - Executable:
message(STATUS "[info] Adding executable 'prgfoo'...")
add_executable(prgfoo prgfoo.cxx)
target_link_libraries(prgfoo PUBLIC Bayeux_jsontools_ex01)
install(TARGETS prgfoo
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  )

message( STATUS "[info] ${PROJECT_NAME}: Exiting.")

# end of CMakeLists.txt
