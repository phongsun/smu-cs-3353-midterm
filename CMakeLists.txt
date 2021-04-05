
cmake_minimum_required(VERSION 3.7)
project(follio)
find_package(Boost REQUIRED)
find_package(folly REQUIRED)
find_package(Threads REQUIRED)
find_package(gflags REQUIRED)

set(CMAKE_CXX_STANDARD 17)
#include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${folly_INCLUDE_DIRS})

set_and_check(FOLLY_INCLUDE_DIR /usr/local/include/folly)
set_and_check(FOLLY_CMAKE_DIR /usr/local/lib/cmake/folly)
if (NOT TARGET Folly::folly)
  include("${FOLLY_CMAKE_DIR}/folly-targets.cmake")
endif()


set(FOLLY_LIBRARIES Folly::folly)

if (NOT folly_FIND_QUIETLY)
  message(STATUS "Found folly: ${PACKAGE_PREFIX_DIR}")
endif()

add_executable(follio main.cpp)
target_link_libraries(follio ${Boost_LIBRARIES} ${FOLLY_LIBRARIES})