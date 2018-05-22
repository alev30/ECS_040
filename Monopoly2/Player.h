//
// Created by Adam Levin on 2/6/18.
//

#ifndef PLAYER_H
#define PLAYER_H


#include "Property.h"



class Player {
private:
    int position;
    int cash;
    std::vector<Property> user_properties;
    int player_num;
    bool roll;
    std:: string playerName;
    int rollCount;
    std::vector<int> propSetOwner;
    bool setOwner;
    bool upgradeOwner;
public:
    bool isUpgradeOwner() const;

    void setUpgradeOwner(bool upgradeOwner);

    bool isSetOwner() const;

    void setSetOwner(bool setOwner);

    std::vector<int> &getPropSetOwner();

    void setPropSetOwner(const std::vector<int> &propSetOwner);


    int getRollCount() const;

    void setRollCount(int rollCount);

    std::string &getPlayerName() ;

    void setPlayerName( std::string &playerName);


    void addProperty(Property aProperty);

    int getPosition() ;

    void setPosition(int position);

    int getCash() ;

    void setCash(int cash);

    std::vector<Property> &getUser_properties();

    void setUser_properties( std::vector<Property> &user_properties);

    int getPlayer_num() ;

    void setPlayer_num(int player_num);

    bool isRoll() ;

    void setRoll(bool roll);
};


#endif
