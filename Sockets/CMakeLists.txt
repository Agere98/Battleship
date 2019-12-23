cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

project("Sockets")

add_library(sockets STATIC SocketBSD.cpp)

target_include_directories(sockets INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
