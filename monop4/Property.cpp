//
// Created by Adam Levin on 2/26/18.
//

#include "Property.h"
#include <cmath>


void Monopoly::Property::display()  {
    std:: cout << getSpaceNum() << "\t|" << getSpaceName() << "\t|";

    if (getOwner()!= -1){
        std::cout << getPropertyOwnerName();
    }
    else{
        std::cout << "None";
    }
    std::cout << "\t|";
    if (isHasUpgrades()){
        for (int i = 0; i < getHouses(); ++i){
            std::cout << "h";
        }
        for (int j = 0; j< getHotels(); ++j){
            std::cout << "H";
        }
        std::cout << "\t|";
    }
    else{
        std::cout << "\t|";
    }

}



/*void Monopoly::Property::propertyCopy(Property &prop) {

    setSpaceName(prop.getSpaceName());
    setSpaceNum(prop.getSpaceNum());
    setSpaceType(prop.getSpaceType());
    setMostUpgrades(prop.isMostUpgrades());
    setHotels(prop.getHotels());
    setHotelRent(prop.getHotelRent());
    setHouseRent(getHouseRent());
    setHouses(prop.getHouses());
    setNormalRent(prop.getNormalRent());
    setSubSetID(prop.getSubSetID());
    setOwner(prop.getOwner());
    setPrice(prop.getPrice());
    setSetID(prop.getSetID());
    setHouseCost(prop.getHouseCost());
    setHotelCost(prop.getHotelCost());
}*/

void Monopoly::Property::activate(Monopoly::Player &player) {
    //put in options for upgrades, purchase, rent, houses, hotels,


    Monopoly::Property tempProp(*this);



    if (getOwner() == -1 && player.getCash() >= getPrice()) {

        std::cout << "Would you like to buy " << getSpaceName() << " for $" << getPrice() << "?"
                  << std::endl;
        std::cout << "Rent on " << getSpaceName() << " is $" << getNormalRent() << std::endl;
        std::cout << "Enter y for yes or n for no: " << std::endl;
        char buy;
        std::cin >> buy;


        if (buy == 'y') {
            std::cout << player.getPlayerName() << " bought " << getSpaceName() << " for $" << getPrice()
                      << std::endl;
            setOwner(player.getPlayer_num());
            setPropertyOwnerName(player.getPlayerName());
            tempProp.setOwner(player.getPlayer_num());
            tempProp.setPropertyOwnerName(player.getPlayerName());
            player.getUser_properties().push_back(tempProp);
            player.setCash(player.getCash() - getPrice());
            player.setJustPurchased(true);
        }


            //branch for Auctioning property if property has no owner, auction rules is set...
        else if (buy == 'n' && player.isAuction()) {
            player.setAuctionTurn(true);
            player.setAuctionPropertyPrice(getPrice());
        }
    }

    else if (getOwner() == -1 && player.getCash() < getPrice() && player.isAuction()) {
        // comment if they dont have enough money
        player.setAuctionTurn(true);
        player.setAuctionPropertyPrice(getPrice());
    }
    else if (getOwner() == -1 && player.getCash() < getPrice() && !player.isAuction()) {
        // commment if they dont have enough $$
        std::cout << player.getPlayerName() << ", you don't have enough money to afford " << getSpaceName() << "."
                  << std::endl;
        std::cout << getSpaceName() << " costs $" << getPrice() << " but you only have $" << player.getCash()
                  << std::endl;
    }
        // player lands on their own property //
    else if (getOwner() == player.getPlayer_num()) {
        std::cout << player.getPlayerName() << ", you landed on " << getSpaceName() << "which you already own"
                  << std::endl;
    }

        // someone else owns the property //
    else if (getOwner() != player.getPlayer_num() && getOwner() != -1 && player.getPosition() != 0) {

        if (isPropertySet() && isHasUpgrades()) {
            // has enough money to pay off an upgraded property //
            if (player.getCash() >= ((getHouseRent() * static_cast<int>(pow(2, getHouses() - 1))) + getHotelRent())) {
                player.setCash(player.getCash() -
                               ((getHouseRent() * static_cast<int>(pow(2, getHouses() - 1))) + getHotelRent()));
                player.setCashToPay((getHouseRent() * static_cast<int>(pow(2, getHouses() - 1))) + getHotelRent());
                player.setNeedToPay(true);
                player.setPlayerToPay(getOwner());
                player.setSpacePaid(getSpaceName());
            }
                // bankruptcy loop //
            else {
                player.setPlayerToPay(getOwner());
                player.setCashToPay(player.getCash());
                player.setCash(0);
                player.setNeedToPay(true);
                player.setBrokeToPlayer(true);
                player.setSpacePaid(getSpaceName());

            }


        } else if (isPropertySet() && !isHasUpgrades()) {
            if (player.getCash() >= getNormalRent() * player.getPropertySetMultiplier()) {
                player.setCash(player.getCash() - getNormalRent() * player.getPropertySetMultiplier());
                player.setCashToPay(getNormalRent() * player.getPropertySetMultiplier());
                player.setNeedToPay(true);
                player.setPlayerToPay(getOwner());
                player.setSpacePaid(getSpaceName());
            }

                // bankruptcy loop //
            else {
                player.setPlayerToPay(getOwner());
                player.setCashToPay(player.getCash());
                player.setCash(0);
                player.setNeedToPay(true);
                player.setBrokeToPlayer(true);
                player.setSpacePaid(getSpaceName());

            }
        } else {
            if (player.getCash() >= getNormalRent()) {
                player.setCash(player.getCash() - getNormalRent());
                player.setCashToPay(getNormalRent());
                player.setNeedToPay(true);
                player.setPlayerToPay(getOwner());
                player.setSpacePaid(getSpaceName());
            } else {
                player.setPlayerToPay(getOwner());
                player.setCashToPay(player.getCash());
                player.setCash(0);
                player.setNeedToPay(true);
                player.setBrokeToPlayer(true);
                player.setSpacePaid(getSpaceName());
            }


        }
    }

}



bool Monopoly::Property::isMostUpgrades() const {
    return mostUpgrades;
}
void Monopoly::Property::setMostUpgrades(bool mostUpgrades) {
    Property::mostUpgrades = mostUpgrades;
}
int Monopoly::Property::getSetID() const {
    return setID;
}
void Monopoly::Property::setSetID(int setID) {
    Property::setID = setID;
}
int Monopoly::Property::getSubSetID() const {
    return subSetID;
}
void Monopoly::Property::setSubSetID(int subSetID) {
    Property::subSetID = subSetID;
}
int Monopoly::Property::getPrice() const {
    return price;
}
void Monopoly::Property::setPrice(int price) {
    Property::price = price;
}
int Monopoly::Property::getHouseCost() const {
    return houseCost;
}
void Monopoly::Property::setHouseCost(int houseCost) {
    Property::houseCost = houseCost;
}
int Monopoly::Property::getHotelCost() const {
    return hotelCost;
}
void Monopoly::Property::setHotelCost(int hotelCost) {
    Property::hotelCost = hotelCost;
}
int Monopoly::Property::getNormalRent() const {
    return normalRent;
}
void Monopoly::Property::setNormalRent(int normalRent) {
    Property::normalRent = normalRent;
}
int Monopoly::Property::getHouseRent() const {
    return houseRent;
}
void Monopoly::Property::setHouseRent(int houseRent) {
    Property::houseRent = houseRent;
}
int Monopoly::Property::getHotelRent() const {
    return hotelRent;
}
void Monopoly::Property::setHotelRent(int hotelRent) {
    Property::hotelRent = hotelRent;
}
int Monopoly::Property::getHouses() const {
    return houses;
}
void Monopoly::Property::setHouses(int houses) {
    Property::houses = houses;
}
int Monopoly::Property::getHotels() const {
    return hotels;
}
void Monopoly::Property::setHotels(int hotels) {
    Property::hotels = hotels;
}
int Monopoly::Property::getOwner() const {
    return owner;
}
void Monopoly::Property::setOwner(int owner) {
    Property::owner = owner;
}

bool Monopoly::Property::isPropertySet() const {
    return propertySet;
}

void Monopoly::Property::setPropertySet(bool propertySet) {
    Property::propertySet = propertySet;
}

bool Monopoly::Property::isHasUpgrades() const {
    return hasUpgrades;
}

void Monopoly::Property::setHasUpgrades(bool hasUpgrades) {
    Property::hasUpgrades = hasUpgrades;
}

const std::string &Monopoly::Property::getPropertyOwnerName() const {
    return propertyOwnerName;
}

void Monopoly::Property::setPropertyOwnerName(const std::string &propertyOwnerName) {
    Property::propertyOwnerName = propertyOwnerName;
}




