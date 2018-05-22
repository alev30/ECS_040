//
// Created by Adam Levin on 2/6/18.
//

#include "Player.h"

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int position) {
    Player::position = position;
}

int Player::getCash() const {
    return cash;
}

void Player::setCash(int cash) {
    Player::cash = cash;
}

const vector<Property> &Player::getUser_properties() const {
    return user_properties;
}

void Player::setUser_properties(const vector<Property> &user_properties) {
    Player::user_properties = user_properties;
}

int Player::getPlayer_num() const {
    return player_num;
}

void Player::setPlayer_num(int player_num) {
    Player::player_num = player_num;
}

bool Player::isRoll() const {
    return roll;
}

void Player::setRoll(bool roll) {
    Player::roll = roll;
}



Move Player::get_move(){
    Move output;
    output.setEnds_turn(false);
    cout<< "Player " << getPlayer_num() << " please choose an action" <<  endl;
    if (!isRoll()){
        cout << "1: Roll Dice" << endl;
        cout << "2: Inspect Player" << endl;
        cout << "3: Leave Game" << endl;
        cout << "Your action: " << endl;
    }
    else{
        cout << "1: End Turn" << endl;
        cout << "2: Inspect Player" << endl;
        cout << "3: Leave Game" << endl;
        cout << "Your action: " << endl;
    }

    int choiceVar;
    cin >> choiceVar;
        output.setChoice(choiceVar);



    return output;
}



