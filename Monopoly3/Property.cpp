//
// Created by Adam Levin on 2/6/18.
//

#include "Property.h"

int Property::getSetID() const {
    return setID;
}

void Property::setSetID(int setID) {
    Property::setID = setID;
}

int Property::getSubsetID() const {
    return subsetID;
}

void Property::setSubsetID(int subsetID) {
    Property::subsetID = subsetID;
}

int Property::getHouses() const {
    return houses;
}

void Property::setHouses(int houses) {
    Property::houses = houses;
}

int Property::getHotels() const {
    return hotels;
}

void Property::setHotels(int hotels) {
    Property::hotels = hotels;
}

int Property::getPrice() const {
    return price;
}

void Property::setPrice(int price) {
    Property::price = price;
}

int Property::getOwner() const {
    return owner;
}

void Property::setOwner(int owner) {
    Property::owner = owner;
}

int Property::getHouse_cost() const {
    return house_cost;
}

void Property::setHouse_cost(int house_cost) {
    Property::house_cost = house_cost;
}

int Property::getHotel_cost() const {
    return hotel_cost;
}

void Property::setHotel_cost(int hotel_cost) {
    Property::hotel_cost = hotel_cost;
}

const string &Property::getName() const {
    return name;
}

void Property::setName(const string &name) {
    Property::name = name;
}

int Property::getRent() const {
    return rent;
}

void Property::setRent(int rent) {
    Property::rent = rent;
}

int Property::getRent_with_hotel() const {
    return rent_with_hotel;
}

void Property::setRent_with_hotel(int rent_with_hotel) {
    Property::rent_with_hotel = rent_with_hotel;
}

int Property::getRent_with_house() const {
    return rent_with_house;
}

void Property::setRent_with_house(int rent_with_house) {
    Property::rent_with_house = rent_with_house;
}

const string &Property::getType() const {
    return type;
}

void Property::setType(const string &type) {
    Property::type = type;
}

int Property::getSpaceNum() const {
    return spaceNum;
}

void Property::setSpaceNum(int spaceNum) {
    Property::spaceNum = spaceNum;
}
