project(call_cache)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
find_package(Boost 1.58 COMPONENTS thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_executable(${PROJECT_NAME} ${SRC_LIST})


