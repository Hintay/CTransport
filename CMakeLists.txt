cmake_minimum_required(VERSION 3.20)
project(CTransport)

set(CMAKE_CXX_STANDARD 20)

add_library(CTransport library.cpp)

add_subdirectory(crc)
include_directories(crc)

target_link_libraries(CTransport crc)

add_subdirectory(tests)
