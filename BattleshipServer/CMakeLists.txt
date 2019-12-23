cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

project("BattleshipServer")

add_executable (BattleshipServer "BattleshipServer.cpp")

target_link_libraries(BattleshipServer PUBLIC sockets)
target_include_directories(BattleshipServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
