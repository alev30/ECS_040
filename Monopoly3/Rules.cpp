//
// Created by Adam Levin on 2/7/18.
//

#include "Rules.h"

int Rules::getStarting_cash() const {
    return starting_cash;
}

void Rules::setStarting_cash(int starting_cash) {
    Rules::starting_cash = starting_cash;
}

int Rules::getTurn_limit() const {
    return turn_limit;
}

void Rules::setTurn_limit(int turn_limit) {
    Rules::turn_limit = turn_limit;
}

int Rules::getPlayer_endgame() const {
    return player_endgame;
}

void Rules::setPlayer_endgame(int player_endgame) {
    Rules::player_endgame = player_endgame;
}

int Rules::getProperty_set_multiplier() const {
    return property_set_multiplier;
}

void Rules::setProperty_set_multiplier(int property_set_multiplier) {
    Rules::property_set_multiplier = property_set_multiplier;
}

int Rules::getHouses_before_hotels() const {
    return houses_before_hotels;
}

void Rules::setHouses_before_hotels(int houses_before_hotels) {
    Rules::houses_before_hotels = houses_before_hotels;
}

bool Rules::isBuild_houses_evenly() const {
    return build_houses_evenly;
}

void Rules::setBuild_houses_evenly(bool build_houses_evenly) {
    Rules::build_houses_evenly = build_houses_evenly;
}

bool Rules::isFreeparking() const {
    return freeparking;
}

void Rules::setFreeparking(bool freeparking) {
    Rules::freeparking = freeparking;
}

bool Rules::isAuction() const {
    return auction;
}

void Rules::setAuction(bool auction) {
    Rules::auction = auction;
}

int Rules::getGo_multiplier() const {
    return go_multiplier;
}

void Rules::setGo_multiplier(int go_multiplier) {
    Rules::go_multiplier = go_multiplier;
}

int Rules::getTurncount() const {
    return turncount;
}

void Rules::setTurncount(int turncount) {
    Rules::turncount = turncount;
}
