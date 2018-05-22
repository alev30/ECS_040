//
// Created by Adam Levin on 2/6/18.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <iostream>

#include <fstream>
#include <sstream>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <istream>



#include "Player.h"
#include "Rules.h"
#include "Board.h"
#include "DiceRoller.h"




class Gamestate {


private:
    std::vector <Player> players;
    int players_amt;
    int player_turn;
    Board board;
    DiceRoller* roller;
    Rules rulesClass;
    int turnCount;
    bool ends_turn;
    int choice;
public:
    bool MaxedOut;

    std::vector<Property> monopoly;

    std::vector<int> subSetCount;

    std::vector<Player> &getPlayers() ;

    void setPlayer( std::vector<Player> &players);

    void make_move(DiceRoller *roll);


    void get_move(int playernumber);

    bool isEnds_turn() const;

    void setEnds_turn(bool ends_turn);

    int getChoice() const;

    void setChoice(int choice);

    Board getBoard();

    void setBoard(Board board);

    int getTurnCount() const;

    void setTurnCount(int turnCount);

    Rules getRulesClass() const;

    void setRulesClass(Rules rulesClass);

    void setup(char* Rules, char* Board);

    bool is_game_over();

    void display_game_state();

    void change_turn();

    void declare_winners();

    int getPlayers_amt() const;

    void setPlayers_amt(int players_amt);

    int getPlayer_turn() const;

    void setPlayer_turn(int player_turn);

    DiceRoller *getRoller() const;

    void setRoller(DiceRoller *roller);


};







#endif
