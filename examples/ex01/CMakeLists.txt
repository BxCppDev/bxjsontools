# - Top level CMakeLists.txt for jsontools_ex01 example program

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(jsontools_ex01)

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

add_definitions(-std=c++11)

# - jsontools_INCLUDE_DIRS and jsontools_LIBRARIES must be set on the command line
set(_incs ${jsontools_INCLUDE_DIRS})
set(_libs ${jsontools_LIBRARIES})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
include_directories(${PROJECT_SOURCE_DIR} ${_incs})
add_library(jsontools_ex01 SHARED
            foo.h
            foo.cc
            )

target_link_libraries(jsontools_ex01 ${_libs} )
install( FILES
         ${PROJECT_BINARY_DIR}/jsontools_ex01{CMAKE_SHARED_LIBRARY_SUFFIX}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
         PERMISSIONS OWNER_READ OWNER_EXECUTE
         GROUP_READ GROUP_EXECUTE
         WORLD_READ WORLD_EXECUTE
       )

add_executable(prgfoo prgfoo.cxx)

target_link_libraries(prgfoo
                      jsontools_ex01
                     )

install ( FILES
    ${PROJECT_BINARY_DIR}/prgfoo
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
