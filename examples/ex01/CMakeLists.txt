# - Top level CMakeLists.txt for jsontools_ex01 example program

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bxjsontools_ex01)

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

find_package(BxJsontools 0.1 REQUIRED CONFIG HINTS )
message(STATUS "BxJsontools_INCLUDE_DIRS='${BxJsontools_INCLUDE_DIRS}'")
message(STATUS "BxJsontools_DEFINITIONS='${BxJsontools_DEFINITIONS}'")
message(STATUS "BxJsontools_LIBRARY='${BxJsontools_LIBRARY}'")

# - jsontools_INCLUDE_DIRS and jsontools_LIBRARIES must be set on the command line
set(_incs ${BxJsontools_INCLUDE_DIRS})
set(_libs ${BxJsontools_LIBRARY})
add_definitions(${BxJsontools_DEFINITIONS})

#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(${PROJECT_SOURCE_DIR} ${_incs})
add_library(Bayeux_jsontools_ex01 SHARED
            foo.h
            foo.cc
            )

target_link_libraries(Bayeux_jsontools_ex01 ${_libs} )
install( FILES
         ${PROJECT_BINARY_DIR}/libBayeux_jsontools_ex01${CMAKE_SHARED_LIBRARY_SUFFIX}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
         PERMISSIONS OWNER_READ OWNER_EXECUTE
         GROUP_READ GROUP_EXECUTE
         WORLD_READ WORLD_EXECUTE
       )

add_executable(prgfoo prgfoo.cxx)

target_link_libraries(prgfoo Bayeux_jsontools_ex01)

install ( FILES
    ${PROJECT_BINARY_DIR}/prgfoo
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
