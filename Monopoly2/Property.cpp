//
// Created by Adam Levin on 2/6/18.
//

#include "Property.h"


int Property::getSetID()  {
    return setID;
}

void Property::setSetID(int setID) {
    Property::setID = setID;
}

int Property::getSubsetID()  {
    return subsetID;
}

void Property::setSubsetID(int subsetID) {
    Property::subsetID = subsetID;
}

int Property::getHouses()  {
    return houses;
}

void Property::setHouses(int houses) {
    Property::houses = houses;
}

int Property::getHotels()  {
    return hotels;
}

void Property::setHotels(int hotels) {
    Property::hotels = hotels;
}

int Property::getPrice()  {
    return price;
}

void Property::setPrice(int price) {
    Property::price = price;
}

 int Property::getOwner() {
    return owner;
}

void Property::setOwner(int owner) {
    Property::owner = owner;
}

int Property::getHouse_cost()  {
    return house_cost;
}

void Property::setHouse_cost(int house_cost) {
    Property::house_cost = house_cost;
}

int Property::getHotel_cost()  {
    return hotel_cost;
}

void Property::setHotel_cost(int hotel_cost) {
    Property::hotel_cost = hotel_cost;
}

 std::string &Property::getName()  {
    return name;
}

void Property::setName( std::string &name) {
    Property::name = name;
}

int Property::getRent()  {
    return rent;
}

void Property::setRent(int rent) {
    Property::rent = rent;
}

int Property::getRent_with_hotel()  {
    return rent_with_hotel;
}

void Property::setRent_with_hotel(int rent_with_hotel) {
    Property::rent_with_hotel = rent_with_hotel;
}

int Property::getRent_with_house()  {
    return rent_with_house;
}

void Property::setRent_with_house(int rent_with_house) {
    Property::rent_with_house = rent_with_house;
}

 std::string &Property::getType()  {
    return type;
}

void Property::setType( std::string &type) {
    Property::type = type;
}

int Property::getSpaceNum()  {
    return spaceNum;
}

void Property::setSpaceNum(int spaceNum) {
    Property::spaceNum = spaceNum;
}
