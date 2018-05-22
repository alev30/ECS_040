//
// Created by Adam Levin on 2/26/18.
//

#ifndef MONOPOLY_4_PROPERTY_H
#define MONOPOLY_4_PROPERTY_H

#include <string>
#include "Space.h"
#include "Player.h"

namespace Monopoly {
    class Property : public Space {
    public:
        Property() = default;
        Property(const Property& p) = default;
        bool isMostUpgrades() const;
        void setMostUpgrades(bool mostUpgrades);
        int getSetID() const;
        void setSetID(int setID);
        int getSubSetID() const;
        void setSubSetID(int subSetID);
        int getPrice() const;
        void setPrice(int price);
        int getHouseCost() const;
        void setHouseCost(int houseCost);
        int getHotelCost() const;
        void setHotelCost(int hotelCost);
        int getNormalRent() const;
        void setNormalRent(int normalRent);
        int getHouseRent() const;
        void setHouseRent(int houseRent);
        int getHotelRent() const;
        void setHotelRent(int hotelRent);
        int getHouses() const;
        void setHouses(int houses);
        int getHotels() const;
        void setHotels(int hotels);
        int getOwner() const;
        void setOwner(int owner);
        bool isPropertySet() const;
        void setPropertySet(bool propertySet);
        bool isHasUpgrades() const;
        void setHasUpgrades(bool hasUpgrades);
        const std::string &getPropertyOwnerName() const;
        void setPropertyOwnerName(const std::string &propertyOwnerName);
        void activate(Monopoly::Player &player)  ;
        void display()  ;
        //void propertyCopy(Property &prop);

    private:
        std::string propertyOwnerName;
        bool mostUpgrades;
        bool hasUpgrades;
        int setID;
        int subSetID;
        int price;
        int houseCost;
        int hotelCost;
        int normalRent;
        int houseRent;
        int hotelRent;
        int houses;
        int hotels;
        int owner;
        bool propertySet;
    };
}


#endif //MONOPOLY_4_PROPERTY_H
