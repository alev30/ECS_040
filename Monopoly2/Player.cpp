//
// Created by Adam Levin on 2/6/18.
//

#include "Player.h"





int Player::getPosition()  {
    return position;
}

void Player::setPosition(int position) {
    Player::position = position;
}

int Player::getCash()  {
    return cash;
}

void Player::setCash(int cash) {
    Player::cash = cash;
}

std::vector<Property> &Player::getUser_properties()  {
    return user_properties;
}

void Player::setUser_properties( std::vector<Property> &user_properties) {
    Player::user_properties = user_properties;
}

int Player::getPlayer_num()  {
    return player_num;
}

void Player::setPlayer_num(int player_num) {
    Player::player_num = player_num;
}

bool Player::isRoll()  {
    return roll;
}

void Player::setRoll(bool roll) {
    Player::roll = roll;
}

void Player::addProperty(Property aProperty){
    getUser_properties().push_back(aProperty);

}




std::string &Player::getPlayerName()  {
    return playerName;
}

void Player::setPlayerName(std::string &playerName) {
    Player::playerName = playerName;
}

int Player::getRollCount() const {
    return rollCount;
}

void Player::setRollCount(int rollCount) {
    Player::rollCount = rollCount;
}

std::vector<int> &Player::getPropSetOwner()  {
    return propSetOwner;
}

void Player::setPropSetOwner(const std::vector<int> &propSetOwner) {
    Player::propSetOwner = propSetOwner;
}

bool Player::isSetOwner() const {
    return setOwner;
}

void Player::setSetOwner(bool setOwner) {
    Player::setOwner = setOwner;
}

bool Player::isUpgradeOwner() const {
    return upgradeOwner;
}

void Player::setUpgradeOwner(bool upgradeOwner) {
    Player::upgradeOwner = upgradeOwner;
}

