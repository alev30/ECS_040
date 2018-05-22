//
// Created by Adam Levin on 2/6/18.
//

#ifndef MONOPOLY_2_PLAYER_H
#define MONOPOLY_2_PLAYER_H

#include <vector>
#include "Property.h"
#include "Move.h"

class Player {
private:
    int position;
    int cash;
    vector<Property> user_properties;
    int player_num;
    bool roll;
public:
    Move get_move();

    int getPosition() const;

    void setPosition(int position);

    int getCash() const;

    void setCash(int cash);

    const vector<Property> &getUser_properties() const;

    void setUser_properties(const vector<Property> &user_properties);

    int getPlayer_num() const;

    void setPlayer_num(int player_num);

    bool isRoll() const;

    void setRoll(bool roll);
};


#endif MONOPOLY_2_PLAYER_H
