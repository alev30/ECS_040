//
// Created by Adam Levin on 2/6/18.
//

#ifndef MOVE_H
#define MOVE_H

#include "Gamestate.h"
#include <vector>
#include "Player.h"


class Move {
private:
    bool ends_turn;
    int choice;
public:
    void make_move(Move *move, Gamestate *gamestate);

    bool isEnds_turn() const;

    void setEnds_turn(bool ends_turn);

    int getChoice() const;

    void setChoice(int choice);
};


#endif //MONOPOLY_2_MOVE_H
