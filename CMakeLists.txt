# - Top level CMakeLists.txt for Bayeux/Jsontools C++ library

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(bxjsontools LANGUAGES CXX)

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
set(BxJsontools_VERSION_MAJOR 0)
set(BxJsontools_VERSION_MINOR 1)
set(BxJsontools_VERSION_PATCH 0)
set(BxJsontools_VERSION
  "${BxJsontools_VERSION_MAJOR}.${BxJsontools_VERSION_MINOR}.${BxJsontools_VERSION_PATCH}")

#-----------------------------------------------------------------------
# - Standard UNIX Tool install paths, including relative paths for use
# by applications requiring resources
include(GNUInstallDirs)

# - Validate that certain paths are relative, otherwise relocation may fail
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "[fatal] Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()

# Add a path for CMake config files
set(CMAKE_INSTALL_CMAKEDIR      ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# Resources directories based on name-version subdirs
set(BxJsontools_TAG "BxJsontools-${BxJsontools_VERSION}")
file(RELATIVE_PATH BXJSONTOOLS_BINDIR_TO_RESOURCEDIR
  "${CMAKE_INSTALL_FULL_BINDIR}"
  "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BxJsontools_TAG}"
  )
file(RELATIVE_PATH BXJSONTOOLS_CMAKEDIR_TO_INCLUDEDIR
  "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BxJsontools_TAG}"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
  )
message(STATUS "[info] BXJSONTOOLS_BINDIR_TO_RESOURCEDIR  = '${BXJSONTOOLS_BINDIR_TO_RESOURCEDIR}'")
message(STATUS "[info] BXJSONTOOLS_CMAKEDIR_TO_INCLUDEDIR = '${BXJSONTOOLS_CMAKEDIR_TO_INCLUDEDIR}'")

set(BxJsoncpp_HEADERS
  src/json/json-forwards.h
  src/json/json.h
  )

set(BxJsontools_HEADERS
  src/jsontools/core.h
  src/jsontools/exception.h
  src/jsontools/node.h
  src/jsontools/node-inl.h
  src/jsontools/base_type_converters.h
  src/jsontools/std_type_converters.h
  src/jsontools/serdes.h
  src/jsontools/io.h
  src/jsontools/io-inl.h
  src/jsontools/iofile.h
  src/jsontools/iofile-inl.h
  src/jsontools/i_jsonizable.h
  src/jsontools/jsontools.h
  )

set(BxJsontools_SOURCES
  src/jsontools/i_jsonizable.cc
  src/jsontools/exception.cc
  src/jsontools/node.cc
  src/json/jsoncpp.cpp
  )

set(BxJsontools_OTHER_LIBS)

set(BXJSONTOOLS_BOOST_MIN_VERSION 1.58.0)
set(BXJSONTOOLS_BOOST_COMPONENTS date_time)
message( STATUS "[info] Finding Boost version > ${BXJSONTOOLS_BOOST_MIN_VERSION} and components '${BXJSONTOOLS_BOOST_COMPONENTS}'")
find_package(Boost ${BXJSONTOOLS_BOOST_MIN_VERSION}
  REQUIRED
  ${BXJSONTOOLS_BOOST_COMPONENTS}
  )
message( STATUS "[info] Boost_VERSION      = '${Boost_VERSION}'")
message( STATUS "[info] Boost_INCLUDE_DIRS = '${Boost_INCLUDE_DIRS}'")
message( STATUS "[info] Boost_LIBRARIES    = '${Boost_LIBRARIES}'")
set(Boost_USE_CONFIG 0)
if (Boost_MAJOR_VERSION)
  # MODULE:  Example: /usr/share/cmake-X.Y/Modules/FindBoost.cmake:
  message( STATUS "[info] Found Boost through 'MODULE' mode.")
  message( STATUS "[info] Found Boost_LIB_VERSION  = '${Boost_LIB_VERSION}'")
  message( STATUS "[info] Found Boost_MAJOR_VERSION    = '${Boost_MAJOR_VERSION}'")
  message( STATUS "[info] Found Boost_MINOR_VERSION    = '${Boost_MINOR_VERSION}'")
  message( STATUS "[info] Found Boost_SUBMINOR_VERSION = '${Boost_SUBMINOR_VERSION}'")
  set(BxJsontools_BOOST_VERSION
    "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
  get_filename_component(Boost_DIR ${Boost_INCLUDE_DIRS} DIRECTORY)
else()
  # CONFIG:  Example: [Cadfaelbrew/install/dir]/lib/cmake/Boost-1.XX.Y/BoostConfig.cmake:
  message( STATUS "[info] Found Boost through 'CONFIG' mode.")
  set(Boost_USE_CONFIG 1)
  string(REPLACE "_" "." BxJsontools_BOOST_VERSION ${Boost_VERSION})
endif()
message( STATUS "[info] BxJsontools_BOOST_VERSION    = '${BxJsontools_BOOST_VERSION}'")
set(BxJsontools_BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${BxJsontools_BOOST_INCLUDE_DIRS})
list(APPEND
  BxJsontools_HEADERS
  src/jsontools/boost_type_converters.h
  )
list(APPEND BxJsontools_OTHER_LIBS
  ${Boost_DATE_TIME_LIBRARY}
  )
message( STATUS "[info] BxJsontools_OTHER_LIBS = '${BxJsontools_OTHER_LIBS}'")

# - Publish headers
configure_file(src/jsontools/version.h.in ${PROJECT_BINARY_DIR}/src/jsontools/version.h @ONLY)
configure_file(src/jsontools/config.h.in  ${PROJECT_BINARY_DIR}/src/jsontools/config.h  @ONLY)

set(BxJsontools_PRIVATE_HEADERS
  )

set(BXJSONTOOLS_DEFINITIONS
  -std=c++11
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS ${BXJSONTOOLS_DEFINITIONS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

add_library(Bayeux_jsontools SHARED
  ${BxJsoncpp_HEADERS}
  ${BxJsontools_HEADERS}
  ${BxJsontools_PRIVATE_HEADERS}
  ${BxJsontools_SOURCES}
  )

# Not used:
# # -- RPATH settings --
# # From: https://cmake.org/Wiki/CMake_RPATH_handling
# # use, i.e. don't skip the full RPATH for the build tree
# set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# # when building, don't use the install RPATH already
# # (but later on when installing)
# set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# # add the automatically determined parts of the RPATH
# # which point to directories outside the build tree to the install RPATH
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# # the RPATH to be used when installing, but only if it's not a system directory
# list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
# if("${isSystemDir}" STREQUAL "-1")
#   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
# endif()

target_link_libraries(Bayeux_jsontools ${BxJsontools_OTHER_LIBS})

# - Set RPATH as needed
set_target_properties(Bayeux_jsontools PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)

# - Use BinReloc
set_target_properties(Bayeux_jsontools PROPERTIES COMPILE_DEFINITIONS ENABLE_BINRELOC)

# - Utilities
configure_file(src/utilities/bxjsontools-query.in
  ${PROJECT_BINARY_DIR}/src/utilities/bxjsontools-query
  @ONLY)

install( FILES
  ${BxJsontools_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/jsontools
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${PROJECT_BINARY_DIR}/src/jsontools/version.h
  ${PROJECT_BINARY_DIR}/src/jsontools/config.h
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/jsontools
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${BxJsoncpp_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/json
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${PROJECT_BINARY_DIR}/libBayeux_jsontools${CMAKE_SHARED_LIBRARY_SUFFIX}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_BINARY_DIR}/src/utilities/bxjsontools-query
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/examples
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxJsontools_TAG}
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxJsontools_TAG}
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
)

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/licensing
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxJsontools_TAG}
  FILE_PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

option(BXJSONTOOLS_ENABLE_TESTING "Build unit testing system for Bayeux/jsontools" ON)
if(BXJSONTOOLS_ENABLE_TESTING)
  enable_testing()
endif()

set(BxJsontools_TESTS
  src/jsontools/testing/test_jsontools_0.cxx
  )

if(BXJSONTOOLS_ENABLE_TESTING)
  foreach(_testsource ${BxJsontools_TESTS})
    set(_bxjsontools_TEST_ENVIRONMENT
      # "BXJSONTOOLS_RESOURCE_FILES_DIR=${PROJECT_SOURCE_DIR}/resources"
      )
    get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "bxjsontools-${_testname}")
    add_executable(${_testname} ${_testsource}
      src/jsontools/testing/test.h
      src/jsontools/testing/test.cc
      )
    target_link_libraries(${_testname} Bayeux_jsontools ${BxJsontools_OTHER_LIBS})
    # - On Apple, ensure dynamic_lookup of undefined symbols
    if(APPLE)
      set_target_properties(${_testname} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif()
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_property(TEST ${_testname}
      APPEND PROPERTY ENVIRONMENT ${_bxjsontools_TEST_ENVIRONMENT}
      )
    # - For now, dump them into the testing output directory
    set_target_properties(${_testname}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxjsontools_tests
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxjsontools_tests
      )
  endforeach()
endif()

#-----------------------------------------------------------------------
# Install targets and resources
#
install(TARGETS Bayeux_jsontools
  EXPORT  BxJsontoolsTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

#-----------------------------------------------------------------------
# Configure/Install support files
# Done here so that external package variables are visible
#
# - Targets
export(TARGETS Bayeux_jsontools
  FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}/BxJsontoolsTargets.cmake
  )
install(EXPORT BxJsontoolsTargets
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}
  )

# - Versioning (build and install trees)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxJsontoolsConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}/BxJsontoolsConfigVersion.cmake
  @ONLY
  )

# - Config (build and install trees *at present*)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxJsontoolsConfig.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}/BxJsontoolsConfig.cmake
  @ONLY
  )

install(FILES
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}/BxJsontoolsConfigVersion.cmake
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}/BxJsontoolsConfig.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BxJsontools_TAG}
  )

# - end of CMakeLists.txt
