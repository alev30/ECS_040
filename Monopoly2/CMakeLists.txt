cmake_minimum_required(VERSION 3.9)
project(Monopoly_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Monopoly_2 main.cpp Gamestate.h Gamestate.cpp Property.h Property.cpp Player.h Player.cpp Space.h Space.cpp Rules.h Rules.cpp Board.h Board.cpp DiceRoller.h DiceRoller.cpp )