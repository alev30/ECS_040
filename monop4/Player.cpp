//
// Created by Adam Levin on 2/26/18.
//

#include "Player.h"



int Monopoly::Player::getPosition() const {
    return position;
}

void Monopoly::Player::setPosition(int position) {
    Player::position = position;
}

int Monopoly::Player::getCash() const {
    return cash;
}

void Monopoly::Player::setCash(int cash) {
    Player::cash = cash;
}



int Monopoly::Player::getPlayer_num() const {
    return player_num;
}

void Monopoly::Player::setPlayer_num(int player_num) {
    Player::player_num = player_num;
}

const std::string &Monopoly::Player::getPlayerName() const {
    return playerName;
}

void Monopoly::Player::setPlayerName(const std::string &playerName) {
    Player::playerName = playerName;
}

int Monopoly::Player::getRollCount() const {
    return rollCount;
}

void Monopoly::Player::setRollCount(int rollCount) {
    Player::rollCount = rollCount;
}

std::vector<int> &Monopoly::Player::getPropSetOwner() {
    return propSetOwner;
}

void Monopoly::Player::setPropSetOwner(const std::vector<int> &propSetOwner) {
    Player::propSetOwner = propSetOwner;
}

bool Monopoly::Player::isSetOwner() const {
    return setOwner;
}

void Monopoly::Player::setSetOwner(bool setOwner) {
    Player::setOwner = setOwner;
}

bool Monopoly::Player::isUpgradeOwner() const {
    return upgradeOwner;
}

void Monopoly::Player::setUpgradeOwner(bool upgradeOwner) {
    Player::upgradeOwner = upgradeOwner;
}

int Monopoly::Player::getNetWorth() const {
    return netWorth;
}

void Monopoly::Player::setNetWorth(int netWorth) {
    Player::netWorth = netWorth;
}

int Monopoly::Player::getGoMultiplier() const {
    return goMultiplier;
}

void Monopoly::Player::setGoMultiplier(int goMultiplier) {
    Player::goMultiplier = goMultiplier;
}

int Monopoly::Player::getGoCash() const {
    return goCash;
}

void Monopoly::Player::setGoCash(int goCash) {
    Player::goCash = goCash;
}

std::vector<Monopoly::Property> &Monopoly::Player::getUser_properties() {
    return user_properties;
}

/*void Monopoly::Player::setUser_properties(std::vector<Property> &user_properties) {
    Player::user_properties = user_properties;
}*/

bool Monopoly::Player::isAuction() const {
    return auction;
}

void Monopoly::Player::setAuction(bool auction) {
    Player::auction = auction;
}

bool Monopoly::Player::isNeedToPay() const {
    return needToPay;
}

void Monopoly::Player::setNeedToPay(bool needToPay) {
    Player::needToPay = needToPay;
}

int Monopoly::Player::getPlayerToPay() const {
    return playerToPay;
}

void Monopoly::Player::setPlayerToPay(int playerToPay) {
    Player::playerToPay = playerToPay;
}

int Monopoly::Player::getCashToPay() const {
    return cashToPay;
}

void Monopoly::Player::setCashToPay(int cashToPay) {
    Player::cashToPay = cashToPay;
}

bool Monopoly::Player::isBrokeToPlayer() const {
    return brokeToPlayer;
}

void Monopoly::Player::setBrokeToPlayer(bool brokeToPlayer) {
    Player::brokeToPlayer = brokeToPlayer;
}

const std::string &Monopoly::Player::getSpacePaid() const {
    return spacePaid;
}

void Monopoly::Player::setSpacePaid(const std::string &spacePaid) {
    Player::spacePaid = spacePaid;
}

int Monopoly::Player::getPropertySetMultiplier() const {
    return propertySetMultiplier;
}

void Monopoly::Player::setPropertySetMultiplier(int propertySetMultiplier) {
    Player::propertySetMultiplier = propertySetMultiplier;
}

int Monopoly::Player::getTurnsInJail() const {
    return turnsInJail;
}

void Monopoly::Player::setTurnsInJail(int turnsInJail) {
    Player::turnsInJail = turnsInJail;
}

int Monopoly::Player::getAuctionPropertyPrice() const {
    return auctionPropertyPrice;
}

void Monopoly::Player::setAuctionPropertyPrice(int auctionPropertyPrice) {
    Player::auctionPropertyPrice = auctionPropertyPrice;
}

bool Monopoly::Player::isAuctionTurn() const {
    return auctionTurn;
}

void Monopoly::Player::setAuctionTurn(bool auctionTurn) {
    Player::auctionTurn = auctionTurn;
}

int Monopoly::Player::getPayFP() const {
    return payFP;
}

void Monopoly::Player::setPayFP(int payFP) {
    Player::payFP = payFP;
}

bool Monopoly::Player::isJustVisiting() const {
    return justVisiting;
}

void Monopoly::Player::setJustVisiting(bool justVisiting) {
    Player::justVisiting = justVisiting;
}

bool Monopoly::Player::isFirstTurnInJail() const {
    return firstTurnInJail;
}

void Monopoly::Player::setFirstTurnInJail(bool firstTurnInJail) {
    Player::firstTurnInJail = firstTurnInJail;
}

bool Monopoly::Player::isBankrupt() const {
    return bankrupt;
}

void Monopoly::Player::setBankrupt(bool bankrupt) {
    Player::bankrupt = bankrupt;
}

int Monopoly::Player::getHousesb4hotels() const {
    return housesb4hotels;
}

void Monopoly::Player::setHousesb4hotels(int housesb4hotels) {
    Player::housesb4hotels = housesb4hotels;
}

bool Monopoly::Player::isHasDowngraded() const {
    return hasDowngraded;
}

void Monopoly::Player::setHasDowngraded(bool hasDowngraded) {
    Player::hasDowngraded = hasDowngraded;
}

bool Monopoly::Player::isFreeParking() const {
    return freeParking;
}

void Monopoly::Player::setFreeParking(bool freeParking) {
    Player::freeParking = freeParking;
}

bool Monopoly::Player::isSentToJail() const {
    return sentToJail;
}

void Monopoly::Player::setSentToJail(bool sentToJail) {
    Player::sentToJail = sentToJail;
}

bool Monopoly::Player::isJustPurchased() const {
    return justPurchased;
}

void Monopoly::Player::setJustPurchased(bool justPurchased) {
    Player::justPurchased = justPurchased;
}

bool Monopoly::Player::isPropertyMaxed() const {
    return propertyMaxed;
}

void Monopoly::Player::setPropertyMaxed(bool propertyMaxed) {
    Player::propertyMaxed = propertyMaxed;
}

std::vector<int> &Monopoly::Player::getSubsetAmt(){
    return subsetAmt;
}

void Monopoly::Player::setSubsetAmt(const std::vector<int> &subsetAmt) {
    Player::subsetAmt = subsetAmt;
}


