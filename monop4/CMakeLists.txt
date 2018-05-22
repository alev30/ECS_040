cmake_minimum_required(VERSION 3.9)
project(Monopoly_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Monopoly_4 main.cpp Gamestate.cpp Gamestate.h DiceRoller.cpp DiceRoller.h Space.cpp Space.h Player.cpp Player.h Property.cpp Property.h Board.cpp Board.h Rules.cpp Rules.h)