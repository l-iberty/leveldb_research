cmake_minimum_required(VERSION 3.9)
project(leveldb_test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(leveldb_test ${SOURCE_FILES})
target_link_libraries(leveldb_test leveldb)