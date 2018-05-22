//
// Created by Adam Levin on 2/28/18.
//

#include "Rules.h"


void Monopoly::Rules::ruleSetup(char *RuleFile) {



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
    setStarting_cash(tempStartCash);

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setTurn_limit(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setPlayer_endgame(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);


    setProperty_set_multiplier(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setHouses_before_hotels(std::stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    if (buffer == "Yes\r"){
        setBuild_houses_evenly(true);
    }
    else{
        setBuild_houses_evenly(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);


    if (buffer == "Yes\r"){
        setFreeparking(true);
    }
    else{
        setFreeparking(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    if (buffer == "Yes\r"){
        setAuction(true);
    }
    else{
        setAuction(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);



    setGo_multiplier(stoi(buffer));



    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setMaxDoublesReRolls(stoi(buffer));


    file.close();


}

int Monopoly::Rules::getStarting_cash() const {
    return starting_cash;
}

void Monopoly::Rules::setStarting_cash(int starting_cash) {
    Rules::starting_cash = starting_cash;
}

int Monopoly::Rules::getTurn_limit() const {
    return turn_limit;
}

void Monopoly::Rules::setTurn_limit(int turn_limit) {
    Rules::turn_limit = turn_limit;
}

int Monopoly::Rules::getPlayer_endgame() const {
    return player_endgame;
}

void Monopoly::Rules::setPlayer_endgame(int player_endgame) {
    Rules::player_endgame = player_endgame;
}

int Monopoly::Rules::getProperty_set_multiplier() const {
    return property_set_multiplier;
}

void Monopoly::Rules::setProperty_set_multiplier(int property_set_multiplier) {
    Rules::property_set_multiplier = property_set_multiplier;
}

int Monopoly::Rules::getHouses_before_hotels() const {
    return houses_before_hotels;
}

void Monopoly::Rules::setHouses_before_hotels(int houses_before_hotels) {
    Rules::houses_before_hotels = houses_before_hotels;
}

bool Monopoly::Rules::isBuild_houses_evenly() const {
    return build_houses_evenly;
}

void Monopoly::Rules::setBuild_houses_evenly(bool build_houses_evenly) {
    Rules::build_houses_evenly = build_houses_evenly;
}

bool Monopoly::Rules::isFreeparking() const {
    return freeparking;
}

void Monopoly::Rules::setFreeparking(bool freeparking) {
    Rules::freeparking = freeparking;
}

bool Monopoly::Rules::isAuction() const {
    return auction;
}

void Monopoly::Rules::setAuction(bool auction) {
    Rules::auction = auction;
}

int Monopoly::Rules::getGo_multiplier() const {
    return go_multiplier;
}

void Monopoly::Rules::setGo_multiplier(int go_multiplier) {
    Rules::go_multiplier = go_multiplier;
}

int Monopoly::Rules::getMaxDoublesReRolls() const {
    return maxDoublesReRolls;
}

void Monopoly::Rules::setMaxDoublesReRolls(int maxDoublesReRolls) {
    Rules::maxDoublesReRolls = maxDoublesReRolls;
}


