//
// Created by Adam Levin on 1/10/18.
//

#ifndef MONOPOLY_GAMESTATE_H
#define MONOPOLY_GAMESTATE_H

#include"vector"
using namespace std;


typedef struct _board_space{
    int setID;
    int subsetID;
    int houses;
    int hotels;
    int price;
    int owner;
    int house_cost;
    int hotel_cost;
    string name;
    int rent;
    int rent_with_hotel;
    int rent_with_house;
    string type;
    int spaceNum;
}board_space;


typedef struct _Player{
    int position;
    int cash;
    vector<board_space> user_properties;
    int player_num;
    bool roll;
}Player;



typedef struct _Gamestate{
    int spaceCount;
    Player* players;
    int players_amt;
    int player_turn;
    board_space* properties;
    ifstream *random;
    int starting_cash;
    int turn_limit;
    int player_endgame;
    int property_set_multiplier;
    int houses_before_hotels;
    bool build_houses_evenly;
    bool freeparking;
    bool auction;
    int go_multiplier;
    int turncount;
    int maxSetID;
} Gamestate;


typedef struct _Move{
    bool ends_turn;
    int choice;
}Move;





#endif //MONOPOLY_GAMESTATE_H
