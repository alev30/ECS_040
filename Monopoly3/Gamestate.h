//
// Created by Adam Levin on 2/6/18.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <iostream>

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <istream>


#include "Property.h"
#include "Player.h"
#include "Rules.h"
#include "Board.h"








class Gamestate {


private:
    int spaceCount;
    Player* players;
    int players_amt;
    int player_turn;
    Property* properties;
    ifstream *random;
    Rules* rules;

public:
    void setup(char* Rules, char* Board, char* RandomNums);
    bool is_game_over();
    void display_game_state();
    void change_turn();
    void declare_winners();

    void delete_game_state();

    int getSpaceCount() const;

    void setSpaceCount(int spaceCount);

    Player *getPlayers() const;

    void setPlayers(Player *players);

    int getPlayers_amt() const;

    void setPlayers_amt(int players_amt);

    int getPlayer_turn() const;

    void setPlayer_turn(int player_turn);

    Property *getProperties() const;

    void setProperties(Property *properties);

    ifstream *getRandom() const;

    void setRandom(ifstream *random);

};







#endif
