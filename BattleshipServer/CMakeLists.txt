cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

project("BattleshipServer")

add_executable (BattleshipServer "BattleshipServer.cpp"
	"ConnectionManager.cpp"
	"Player.cpp"
	"PlayerCommands.cpp"
	"Game.cpp"
	"Matchmaker.cpp")

target_link_libraries(BattleshipServer PUBLIC sockets)
target_include_directories(BattleshipServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
endif(CMAKE_COMPILER_IS_GNUCXX)
