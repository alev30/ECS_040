//
// Created by Adam Levin on 2/7/18.
//

#include "Rules.h"


void Rules::ruleSetup(char *RuleFile) {

    

    std::ifstream file(RuleFile);
    // file.open(RuleFile, 'r');
    std::string buffer;

    if (!file.is_open()){
        std::cout << "File not Open"  <<  std::endl;
    }



    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    std::stringstream input(buffer);
    int tempStartCash;
    input >> tempStartCash;   //file >> buffer;
    this->setStarting_cash(tempStartCash);

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    this->setTurn_limit(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    this->setPlayer_endgame(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);


    this->setProperty_set_multiplier(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    this->setHouses_before_hotels(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    if (buffer == "Yes"){
        this->setBuild_houses_evenly(true);
    }
    else{
        this->setBuild_houses_evenly(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);


    if (buffer == "Yes"){
        this->setFreeparking(true);
    }
    else{
        this->setFreeparking(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    if (buffer == "Yes"){
        this->setAuction(true);
    }
    else{
        this->setAuction(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);



    this->setGo_multiplier(stoi(buffer));



    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    this->setMaxDoublesReRolls(stoi(buffer));


    file.close();

    
}

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

int Rules::getMaxDoublesReRolls() const {
    return maxDoublesReRolls;
}

void Rules::setMaxDoublesReRolls(int maxDoublesReRolls) {
    Rules::maxDoublesReRolls = maxDoublesReRolls;
}


