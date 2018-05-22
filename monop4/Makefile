CC=g++
CFLAGS= -std=c++14 -Wall -Werror -g
SOURCES= main.cpp Property.cpp Gamestate.cpp Player.cpp Space.cpp Rules.cpp Board.cpp DiceRoller.cpp
DEPS= Property.h Gamestate.h Player.h Space.h Rules.h Board.h DiceRoller.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hoarding.out

all: hoarding.out

hoarding.out: main.o Gamestate.o Property.o Player.o Space.o Rules.o Board.o DiceRoller.o
	g++ -g -std=c++14 -Wall -Werror -o hoarding.out main.o Gamestate.o Property.o Player.o Space.o Rules.o Board.o DiceRoller.o

main.o: main.cpp Gamestate.h Property.h Player.h Space.h Rules.h Board.h DiceRoller.h
	g++ -g -std=c++14 -Wall -Werror -c main.cpp

Gamestate.o: Gamestate.cpp Gamestate.h
	g++ -g -std=c++14 -Wall -Werror -c Gamestate.cpp

Property.o: Property.cpp Property.h
	g++ -g -std=c++14 -Wall -Werror -c Property.cpp

Player.o: Player.h Player.cpp
	g++ -g -std=c++14 -Wall -Werror -c Player.cpp

Space.o: Space.h Space.cpp
	g++ -g -std=c++14 -Wall -Werror -c Space.cpp

Rules.o: Rules.h Rules.cpp
	g++ -g -std=c++14 -Wall -Werror -c Rules.cpp

Board.o: Board.h Board.cpp
	g++ -g -std=c++14 -Wall -Werror -c Board.cpp

DiceRoller.o: DiceRoller.h DiceRoller.cpp
	g++ -g -std=c++14 -Wall -Werror -c DiceRoller.cpp

clean:
	-rm -f *.o* hoarding.out