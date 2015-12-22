project(call_cache)
cmake_minimum_required(VERSION 2.8)
set(SRC_LIST main.cpp call_once.h)
find_package(Boost 1.58 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_executable(${PROJECT_NAME} ${SRC_LIST})


