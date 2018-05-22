//
// Created by Adam Levin on 2/6/18.
//

#ifndef MONOPOLY_2_BOARDSPACE_H
#define MONOPOLY_2_BOARDSPACE_H



#include "Gamestate.h"
#include <string>
#include <cstdlib>



class Property {

private:
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
public:
    int getSetID() const;

    void setSetID(int setID);

    int getSubsetID() const;

    void setSubsetID(int subsetID);

    int getHouses() const;

    void setHouses(int houses);

    int getHotels() const;

    void setHotels(int hotels);

    int getPrice() const;

    void setPrice(int price);

    int getOwner() const;

    void setOwner(int owner);

    int getHouse_cost() const;

    void setHouse_cost(int house_cost);

    int getHotel_cost() const;

    void setHotel_cost(int hotel_cost);

    const string &getName() const;

    void setName(const string &name);

    int getRent() const;

    void setRent(int rent);

    int getRent_with_hotel() const;

    void setRent_with_hotel(int rent_with_hotel);

    int getRent_with_house() const;

    void setRent_with_house(int rent_with_house);

    const string &getType() const;

    void setType(const string &type);

    int getSpaceNum() const;

    void setSpaceNum(int spaceNum);
};


#endif MONOPOLY_2_BOARDSPACE_H
