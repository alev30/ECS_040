//
// Created by Adam Levin on 2/6/18.
//

#ifndef PROPERTY_H
#define PROPERTY_H




#include <iostream>


#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>




class Property{

private:
    int setID;
    int subsetID;
    int houses;
    int hotels;
    int price;
    int owner;
    int house_cost;
    int hotel_cost;
    std::string name;
    int rent;
    int rent_with_hotel;
    int rent_with_house;
    std::string type;
    int spaceNum;
public:


    int getSetID() ;

    void setSetID(int setID);

    int getSubsetID() ;

    void setSubsetID(int subsetID);

    int getHouses() ;

    void setHouses(int houses);

    int getHotels() ;

    void setHotels(int hotels);

    int getPrice() ;

    void setPrice(int price);

    int getOwner();

    void setOwner(int owner);

    int getHouse_cost() ;

    void setHouse_cost(int house_cost);

    int getHotel_cost() ;

    void setHotel_cost(int hotel_cost);

     std::string &getName() ;

    void setName( std::string &name);

    int getRent() ;

    void setRent(int rent);

    int getRent_with_hotel() ;

    void setRent_with_hotel(int rent_with_hotel);

    int getRent_with_house() ;

    void setRent_with_house(int rent_with_house);

     std::string &getType() ;

    void setType( std::string &type);

    int getSpaceNum() ;

    void setSpaceNum(int spaceNum);
};


#endif
