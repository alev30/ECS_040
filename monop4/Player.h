//
// Created by Adam Levin on 2/26/18.
//

#ifndef MONOPOLY_4_PLAYER_H
#define MONOPOLY_4_PLAYER_H

#include <string>
#include <vector>



namespace Monopoly {
    class Property;
    class Player {
    public:

        int getPosition() const;

        void setPosition(int position);

        int getCash() const;

        void setCash(int cash);

        std::vector<Property> &getUser_properties();

        //void setUser_properties(std::vector<Property> &user_properties);

        int getPlayer_num() const;

        void setPlayer_num(int player_num);

        const std::string &getPlayerName() const;

        void setPlayerName(const std::string &playerName);

        int getRollCount() const;

        void setRollCount(int rollCount);

        std::vector<int> &getPropSetOwner();

        void setPropSetOwner(const std::vector<int> &propSetOwner);

        bool isSetOwner() const;

        void setSetOwner(bool setOwner);

        bool isUpgradeOwner() const;

        void setUpgradeOwner(bool upgradeOwner);

        int getNetWorth() const;

        void setNetWorth(int netWorth);

        int getGoMultiplier() const;

        void setGoMultiplier(int goMultiplier);

        int getGoCash() const;

        void setGoCash(int goCash);

        bool isAuction() const;

        void setAuction(bool auction);

        bool isNeedToPay() const;

        void setNeedToPay(bool needToPay);

        int getPlayerToPay() const;

        void setPlayerToPay(int playerToPay);

        int getCashToPay() const;

        void setCashToPay(int cashToPay);

        bool isBrokeToPlayer() const;

        void setBrokeToPlayer(bool brokeToPlayer);

        const std::string &getSpacePaid() const;

        void setSpacePaid(const std::string &spacePaid);

        int getPropertySetMultiplier() const;

        void setPropertySetMultiplier(int propertySetMultiplier);

        int getTurnsInJail() const;

        void setTurnsInJail(int turnsInJail);

        int getAuctionPropertyPrice() const;

        void setAuctionPropertyPrice(int auctionPropertyPrice);

        bool isAuctionTurn() const;

        void setAuctionTurn(bool auctionTurn);

        int getPayFP() const;

        void setPayFP(int payFP);

        bool isJustVisiting() const;

        void setJustVisiting(bool justVisiting);

        bool isFirstTurnInJail() const;

        void setFirstTurnInJail(bool firstTurnInJail);

        bool isBankrupt() const;

        void setBankrupt(bool bankrupt);

        int getHousesb4hotels() const;

        void setHousesb4hotels(int housesb4hotels);

        bool isHasDowngraded() const;

        void setHasDowngraded(bool hasDowngraded);

        bool isFreeParking() const;

        void setFreeParking(bool freeParking);

        bool isSentToJail() const;

        void setSentToJail(bool sentToJail);

        bool isJustPurchased() const;

        void setJustPurchased(bool justPurchased);

        bool isPropertyMaxed() const;

        void setPropertyMaxed(bool propertyMaxed);

        std::vector<int> &getSubsetAmt();

        void setSubsetAmt(const std::vector<int> &subsetAmt);

    private:
        std::vector<int> subsetAmt;
        bool justPurchased;
        bool freeParking;
        bool hasDowngraded;
        bool justVisiting;
        int payFP;
        int auctionPropertyPrice;
        int propertySetMultiplier;
        int position;
        int cash;
        std::vector <Property> user_properties;
        int player_num;
        std::string playerName;
        int rollCount;
        std::vector<int> propSetOwner;
        bool setOwner;
        bool upgradeOwner;
        int netWorth;
        int goMultiplier;
        int goCash;
        bool auction;
        bool needToPay;
        int playerToPay;
        int cashToPay;
        bool brokeToPlayer;
        std::string spacePaid;
        int turnsInJail;
        bool auctionTurn;
        bool firstTurnInJail;
        bool bankrupt;
        int housesb4hotels;
        bool sentToJail;
        bool propertyMaxed;
    };
}

#endif //MONOPOLY_4_PLAYER_H
