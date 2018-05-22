//
// Created by Adam Levin on 2/6/18.
//
#include <cmath>
#include "Gamestate.h"







void Gamestate::setup(char* RuleFile, char* BoardFile){

    Player player;
    this->rulesClass.ruleSetup(RuleFile);
    this->board.boardSetup(BoardFile);


    int tempPlayeramt;

    std::cout << "Enter how many players will be playing: ";
    std::cin >> tempPlayeramt;



    this->setTurnCount(0);
    this->setPlayer_turn(0);

    this->setPlayers_amt(tempPlayeramt);




    std::string tempname;

    this->MaxedOut = false;

    std::vector<Player> temp_vec;


    for (int i=0; i<this->getPlayers_amt(); i++) {
        std::cout<< "Enter the name of player " << i + 1 << ": ";
        std::cin>> tempname;
        temp_vec[i].setPlayerName(tempname);
        temp_vec[i].setCash(rulesClass.getStarting_cash());
        temp_vec[i].setPosition(0);
        temp_vec[i].setPlayer_num(i);
        temp_vec[i].setRoll(false);
        temp_vec[i].setRollCount(0);
        temp_vec[i].getPropSetOwner().resize(this->board.getMaxSetID() +1,-1);
        temp_vec[i].setSetOwner(false);
        temp_vec[i].setUpgradeOwner(false);
    }

    this->players= temp_vec;

}




bool Gamestate::is_game_over() {
    bool game_over = false;

    if (this->turnCount >= this->rulesClass.getTurn_limit() && this->rulesClass.getTurn_limit()!=-1){
        game_over = true;
    }

    int players_remaining = 0;
    for (int i = 0; i< this->players_amt; i++){
        if (this->players[i].getPlayer_num() != -1) {
            players_remaining = players_remaining + 1;
        }

    }
    if (players_remaining <= this->rulesClass.getPlayer_endgame()){
        game_over = true;
    }


    return game_over;

// returns false while certain parameters are met depending on input from rule file
// ie turn limit, number of players left to end game,
// bankruptcy function that autokicks player and forfeits properties
}


void Gamestate::display_game_state(){


    int placecount;

    std::cout<< "Space Number | Space Name | Owner  | Upgrades | Players" << std::endl;
    for (int l = 0; l< this->board.getSpaceCount(); l++){
        std::cout << l << "\t\t|  " << this->board.getPropertySet()[l].getName() << "\t| ";
        if (l == 0 ){
            std::cout<< "None\t|";
        }
        else if (this->board.getPropertySet()[l].getOwner()!= -1 ){
            std::cout << this->players[this->board.getPropertySet()[l].getOwner()].getPlayerName() << "\t|";
            /*for(int m=0; m < this->getPlayers_amt(); ++m){
                if (this->board.getPropertySet()[l].getOwner() == m){
                    std::cout<< this->players[m].getPlayerName() << "\t| ";
                }
            }*/
        }
        else{
            std::cout << "None\t| ";
        }

        if ( l == 0){
            std::cout << "\t|" << std::endl;
        }

        else if (this->board.getPropertySet()[l].getHouses()> 0 || this->board.getPropertySet()[l].getHotels()>0 ){
            for (int i = 0; i < this->board.getPropertySet()[l].getHouses(); i++){
                std::cout << "h";
            }
            for (int i = 0; i < this->board.getPropertySet()[l].getHotels(); i++){
                std::cout << "H";
            }
            std::cout << "\t|";
        }


        else{
            std::cout << "\t|";
        }


        placecount = 0;
        for (int k = 0 ; k< this->getPlayers_amt(); k++){
            if (this->players[k].getPosition() == l && this->players[k].getPlayer_num() != -1){
                if (placecount >= 1 ){
                    std::cout << ", ";
                }
                std::cout <<"["<< this->players[k].getPlayerName() << " : $";
                std::cout << this->players[k].getCash() << "]";
                placecount = placecount + 1;
            }

        }
        std::cout << std::endl;
    }




}




void Gamestate::change_turn() {



    for (int i=0; i<this->getPlayers_amt(); i++){

        if (this->player_turn <= this->getPlayers_amt() - 2 &&
            (this->players[this->player_turn + 1].getPlayer_num() != -1)) {
            this->setPlayer_turn(this->player_turn+1); // increment function
            break;
        } else if (this->player_turn == this->getPlayers_amt() - 1 && this->players[0].getPlayer_num() != -1) {
            this->setPlayer_turn(0);

            break;
        }
        else{
            this->setPlayer_turn(player_turn+1);
        }
    }

    if (this->getPlayer_turn() == 0){
        this->setTurnCount(this->getTurnCount() + 1);
    }

}


void Gamestate::declare_winners(){
    std::vector<std::string> finalWinners;
    int maxPrice = 0;

    int playerwinners[getPlayers_amt()];



    for (int i = 0; i < this->getPlayers_amt(); i++){
        if (this->players[i].getPlayer_num() != -1) {
            playerwinners[i] = this->players[i].getCash();
            for (uint j = 0; j < this->players[i].getUser_properties().size(); j++) {
                playerwinners[i] += this->players[i].getUser_properties()[j].getPrice();
                playerwinners[i] += this->players[i].getUser_properties()[j].getHouses()*this->players[i].getUser_properties()[j].getHouse_cost();
                playerwinners[i] += this->players[i].getUser_properties()[j].getHotels()*this->players[i].getUser_properties()[j].getHotel_cost();
            }
        }
        else{
            playerwinners[i] = 0;
        }
    }

    maxPrice = playerwinners[0];

    for (int m = 1; m< getPlayers_amt(); ++m){
        if (playerwinners[m]> playerwinners[m-1]){
            maxPrice = playerwinners[m];
        }
    }


    for (int k = 0; k< this->getPlayers_amt(); k++){
        if (playerwinners[k] == maxPrice){
            finalWinners.push_back(this->players[k].getPlayerName());
        }
    }

    std::cout << "The winners are " << std::endl;


    for (uint l = 0; l < finalWinners.size(); l++) {
        std::cout << finalWinners[l] << std::endl;

    }

}


void Gamestate::make_move(DiceRoller *roll){

    if (!isEnds_turn()) {
        int sellout = 0;
        int upgradeChoice = 0;
        //if (!this->players[player_turn].isRoll()) {
        int move_num = 0;
        int payRentSetID = 0;
        std::string properties_owned = "";  // come back
        int temp_pos = 0;
        int subsetVal = 0;
        int ownerSubsetVal = 0;
        int while_val = 0;
        bool ownsSubset = false;
        //auction temp variables
        int bidAmount = 1;
        int userBid = 0;
        int winnerCount = 0;
        bool someoneHasBid = false;
        int highestBidder = 0;
        bool endAuction = false;
        int auctionCount = 0;
        int maxUpgrades = 0;
        bool evenlyBuilt = false;
        switch (getChoice()) {
            case 1:
                std::cout<< this->players[this->player_turn].getPlayerName() << ", ";
                move_num = roll->dice_roll();

                this->players[this->player_turn].setRoll(true);

                temp_pos = this->players[this->player_turn].getPosition() + move_num;

                if (temp_pos >= this->board.getSpaceCount()) {
                    // this if statements and its nested branches represent passing or landing on go
                    while (temp_pos > this->board.getSpaceCount()-1) {
                        temp_pos -= this->board.getSpaceCount();
                        while_val++;
                    }
                    if (while_val > 0 && temp_pos == 0){
                        this->players[this->player_turn].setCash(this->players[this->player_turn].getCash() +
                                                                 (this->board.getPropertySet()[0].getPrice())*(while_val-1));
                        this->players[this->player_turn].setCash (this->players[this->player_turn].getCash() +
                                                                  (this->board.getPropertySet()[0].getPrice())*(this->getRulesClass().getGo_multiplier()));
                        this->players[this->player_turn].setPosition(temp_pos);

                        if (roll->isDoubles()&&this->players[this->player_turn].getRollCount() < this->getRulesClass().getMaxDoublesReRolls()){
                            this->players[this->player_turn].setRoll(false);
                            this->players[this->player_turn].setRollCount(this->players[this->player_turn].getRollCount()+1);
                            break;
                        }
                        else {
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            this->players[this->player_turn].setRollCount(0);
                            break;
                        }
                    }
                    else if(while_val > 0 && temp_pos != 0){
                        this->players[this->player_turn].setCash(this->players[this->player_turn].getCash() +
                                                                 (this->board.getPropertySet()[0].getPrice())*(while_val));
                        this->players[this->player_turn].setPosition(temp_pos);
                    }

                    if (while_val == 0 && this->players[this->player_turn].getPosition() == 0) {
                        this->players[this->player_turn].setCash ( (this->board.getPropertySet()[0].getPrice())*(this->getRulesClass().getGo_multiplier()));
                        this->players[this->player_turn].setPosition(temp_pos);
                        if (roll->isDoubles()&&this->players[this->player_turn].getRollCount() < this->getRulesClass().getMaxDoublesReRolls()){
                            this->players[this->player_turn].setRoll(false);
                            this->players[this->player_turn].setRollCount(this->players[this->player_turn].getRollCount()+1);
                            break;
                        }
                        else {
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            this->players[this->player_turn].setRollCount(0);
                            break;
                        }
                    }

                }
                else {
                    this->players[this->player_turn].setPosition(temp_pos);

                }
                // property purchase branch

                if (this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()
                    == -1 && this->players[this->player_turn].getCash() >=
                             this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice() ) {
                    //    std::cout << Gamestate->properties[this->players[this->player_turn].position].name << " is "
                    //         << Gamestate->properties[this->players[this->player_turn].position].price << std::endl;


                    std::cout << "Would you like to buy ";
                    std::cout << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                              << " for $"
                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                              << "?" << std::endl;
                    std::cout << "Rent on "
                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                              << " is $";
                    std::cout << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent()
                              << std::endl;
                    //std::cout << "You currently have $" << this->players[this->player_turn].getCash() << std::endl;
                    std::cout << "Enter y for yes or n for no: " << std::endl;
                    char buy;
                    std::cin >> buy;


                    /*char buy;
                    cin >> buy;*/

                    if (buy == 'y') {
                        std::cout << this->players[this->player_turn].getPlayerName() << " bought "
                                  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                  << " for $"
                                  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                  << std::endl;
                        this->board.getPropertySet()[this->players[this->player_turn].getPosition()].setOwner(
                                this->players[this->player_turn].getPlayer_num());

                        this->players[this->player_turn].addProperty(
                                this->board.getPropertySet()[this->players[this->player_turn].getPosition()]);
                        this->players[this->player_turn].setCash(this->players[this->player_turn].getCash() -
                                                                 this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice());


                        for (int i = 0; i <= board.getMaxSetID(); i++) {
                            subsetVal = 0;
                            ownerSubsetVal = 0;
                            for (int j = 1; j < this->board.getSpaceCount(); j++) {
                                if (board.getPropertySet()[j].getSetID() == i) {
                                    subsetVal++;
                                }
                            }
                            for (int k = 0; k < (short) this->players[this->player_turn].getUser_properties().size(); k++) {
                                if (this->players[this->player_turn].getUser_properties()[k].getSetID() == i) {
                                    ownerSubsetVal++;
                                }
                            }
                            if (ownerSubsetVal == subsetVal) {
                                this->players[this->player_turn].getPropSetOwner()[i] = 1;
                                this->players[this->player_turn].setSetOwner(true);
                            }
                        }
                        if (roll->isDoubles() && this->players[this->player_turn].getRollCount() <
                                                 this->getRulesClass().getMaxDoublesReRolls()) {
                            this->players[this->player_turn].setRoll(false);
                            this->players[this->player_turn].setRollCount(
                                    this->players[this->player_turn].getRollCount() + 1);
                            break;
                        } else {
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            this->players[this->player_turn].setRollCount(0);
                            break;
                        }
                    }
                        //branch for Auctioning property if property has no owner, auction rules is set...
                    else if (buy == 'n' && this->rulesClass.isAuction()) {
                        //int Players_amt_in_Auction = this->getPlayers_amt();

                        int tempNoBidder = 0; //iterates if no one bids
                        //tempNoBidder != (short) tempPlayersInAuction.size()
                        std::vector<int> playersAuction (this->players_amt);
                        for (int q = 0; q < this->players_amt; q++){
                            playersAuction[q]= q;
                        }

                        std::cout << "Starting the auction for "
                                  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                  << std::endl;
                        bidAmount = 1;
                        someoneHasBid = false;
                        while (!endAuction) {
                            for (int x = 0; x < this->players_amt; x++) {

                                if (bidAmount == 1) {

                                    std::cout << "No one has bid on "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                              <<
                                              " [$ "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                              << "] yet" << std::endl;
                                    std::cout << this->players[x].getPlayerName()
                                              << ", enter a bid of at least $1 to bid on the property or a value less than that to leave the auction"
                                              << std::endl;
                                    std::cout << "Your bid: ";
                                    //User Input for Bid amount
                                    std::cin >> userBid;
                                    tempNoBidder++;
                                    if (userBid < bidAmount) {
                                        playersAuction[x] = -1;

                                    } else {
                                        highestBidder = x;
                                        bidAmount = userBid;
                                        someoneHasBid = true;
                                        continue;
                                    }
                                    //Ends branch if no player ever decided to Bid, size of vector becomes zero.
                                    auctionCount = 0;
                                    for (int w = 0; w < this->players_amt; w++) {

                                        if (playersAuction[w] != -1) {
                                            auctionCount++;
                                            break;

                                        }
                                    }
                                    if (auctionCount == 0) {

                                        std::cout << "No one decided to purchase "
                                                  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                                  << std::endl;


                                        endAuction = true;
                                        break;

                                    }
                                    /*std::cout << "The current bid for "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                              <<
                                              " [$ "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                              << "] is $" << bidAmount << "by " << this->players[highestBidder].getPlayerName() << std::endl;
                                    std::cout << this->players[x].getPlayerName()
                                              << ", enter a bid of at least $" << bidAmount + 1
                                              << " to bid on the property or a value less than that to leave the auction"
                                              << std::endl;
                                    std::cout << "Your bid: ";
                                    //User Input for Bid amount
                                    std::cin >> userBid;
                                    if (userBid < bidAmount) {
                                        playersAuction[x] = -1;


                                    } else {
                                        highestBidder = x;
                                        bidAmount = userBid;

                                    }*/
                                }

                                if (bidAmount > 1 && playersAuction[x]!= -1) {
                                    std::cout << "The current bid for "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                              <<
                                              " [$ "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                              << "] is $" << bidAmount << "by " << this->players[highestBidder].getPlayerName() << std::endl;
                                    std::cout << this->players[x].getPlayerName()
                                              << ", enter a bid of at least $" << bidAmount + 1
                                              << " to bid on the property or a value less than that to leave the auction"
                                              << std::endl;
                                    std::cout << "Your bid: ";
                                    //User Input for Bid amount
                                    std::cin >> userBid;
                                    if (userBid < bidAmount) {
                                        playersAuction[x] = -1;


                                    } else {
                                        highestBidder = x;
                                        bidAmount = userBid;

                                    }
                                }

                                winnerCount = 0;
                                for (int aa = 0; aa < this->players_amt; aa++) {
                                    if (playersAuction[aa] != -1) {
                                        winnerCount++;
                                    }
                                }
                                if (winnerCount == 1 && someoneHasBid == true) {
                                    std::cout << this->players[highestBidder].getPlayerName() << " won "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                              << " for $" << bidAmount << std::endl;

                                    //Following statements set Auction winner as owner, subtracts amount bidded from cash, ends turn...


                                    //Set owner of property to Auction winner
                                    this->board.getPropertySet()[this->players[this->player_turn].getPosition()].setOwner(
                                            this->players[highestBidder].getPlayer_num());
                                    //Add owned properties to Auction winner
                                    this->players[highestBidder].addProperty(
                                            this->board.getPropertySet()[this->players[this->player_turn].getPosition()]);
                                    //Subtract bid amount from Auction winner cash
                                    this->players[highestBidder].setCash(this->players[highestBidder].getCash() - bidAmount);


                                    subsetVal = 0;
                                    ownerSubsetVal = 0;
                                    for (int i = 0; i <= board.getMaxSetID(); i++) {
                                        for (int j = 1; j < this->board.getSpaceCount(); j++) {
                                            if (board.getPropertySet()[j].getSetID() == i) {
                                                subsetVal++;
                                            }
                                        }
                                        for (int k = 0; k < (short) this->players[x].getUser_properties().size(); k++) {
                                            if (this->players[x].getUser_properties()[k].getSetID() == i) {
                                                ownerSubsetVal++;
                                            }
                                        }
                                        if (ownerSubsetVal == subsetVal) {
                                            this->players[x].getPropSetOwner()[i] = 1;
                                            this->players[x].setSetOwner(true);
                                        }
                                    }

                                    endAuction = true;
                                    break;
                                }
                            }
                        }

                        if (roll->isDoubles() && this->players[this->player_turn].getRollCount() <
                                                 this->getRulesClass().getMaxDoublesReRolls()) {
                            this->players[this->player_turn].setRoll(false);
                            this->players[this->player_turn].setRollCount(
                                    this->players[this->player_turn].getRollCount() + 1);
                            endAuction = true;
                            break;
                        } else {
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            this->players[this->player_turn].setRollCount(0);
                            endAuction = true;
                            break;
                        }

                    }
                    else{
                        if (roll->isDoubles() && this->players[this->player_turn].getRollCount() <
                                                 this->getRulesClass().getMaxDoublesReRolls()) {
                            this->players[this->player_turn].setRoll(false);
                            this->players[this->player_turn].setRollCount(
                                    this->players[this->player_turn].getRollCount() + 1);
                            endAuction = true;
                            break;
                        } else {
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            this->players[this->player_turn].setRollCount(0);
                            endAuction = true;
                            break;
                        }
                    }
                }

                else if (this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()
                    == -1 && this->players[this->player_turn].getCash() <
                             this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice() && this->rulesClass.isAuction()) {
                    //int Players_amt_in_Auction = this->getPlayers_amt();
                    // comment if they dont have enough money

                    int tempNoBidder = 0; //iterates if no one bids
                    //tempNoBidder != (short) tempPlayersInAuction.size()
                    std::vector<int> playersAuction (this->players_amt);
                    for (int q = 0; q < this->players_amt; q++){
                        playersAuction[q]= q;
                    }

                    std::cout << "Starting the auction for "
                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                              << std::endl;
                    bidAmount = 1;
                    someoneHasBid = false;
                    while (!endAuction) {
                        for (int x = 0; x < this->players_amt; x++) {

                            if (bidAmount == 1) {
                                std::cout << "No one has bid on "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                          <<
                                          " [$ "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                          << "] yet" << std::endl;
                                std::cout << this->players[x].getPlayerName()
                                          << ", enter a bid of at least $1 to bid on the property or a value less than that to leave the auction"
                                          << std::endl;
                                std::cout << "Your bid: ";
                                //User Input for Bid amount
                                std::cin >> userBid;
                                tempNoBidder++;
                                if (userBid < bidAmount) {
                                    playersAuction[x] = -1;

                                } else {
                                    highestBidder = x;
                                    bidAmount = userBid;
                                    someoneHasBid = true;
                                    continue;
                                }
                                //Ends branch if no player ever decided to Bid, size of vector becomes zero.
                                auctionCount = 0;
                                for (int w = 0; w < this->players_amt; w++) {

                                    if (playersAuction[w] != -1) {
                                        auctionCount++;
                                        break;

                                    }
                                }
                                if (auctionCount == 0) {

                                    std::cout << "No one decided to purchase "
                                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                              << std::endl;


                                    endAuction = true;
                                    break;

                                }
                                /*
                                std::cout << "The current bid for "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                          <<
                                          " [$ "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                          << "] is $" << bidAmount << "by " << this->players[highestBidder].getPlayerName() << std::endl;
                                std::cout << this->players[x].getPlayerName()
                                          << ", enter a bid of at least $" << bidAmount + 1
                                          << " to bid on the property or a value less than that to leave the auction"
                                          << std::endl;
                                std::cout << "Your bid: ";
                                //User Input for Bid amount
                                std::cin >> userBid;
                                if (userBid < bidAmount) {
                                    playersAuction[x] = -1;


                                } else {
                                    highestBidder = x;
                                    bidAmount = userBid;

                                }*/
                            }

                            if (bidAmount > 1 && playersAuction[x]!= -1) {
                                std::cout << "The current bid for "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                          <<
                                          " [$ "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice()
                                          << "] is $" << bidAmount << "by " << this->players[highestBidder].getPlayerName() << std::endl;
                                std::cout << this->players[x].getPlayerName()
                                          << ", enter a bid of at least $" << bidAmount + 1
                                          << " to bid on the property or a value less than that to leave the auction"
                                          << std::endl;
                                std::cout << "Your bid: ";
                                //User Input for Bid amount
                                std::cin >> userBid;
                                if (userBid < bidAmount) {
                                    playersAuction[x] = -1;


                                } else {
                                    highestBidder = x;
                                    bidAmount = userBid;

                                }
                            }

                            winnerCount = 0;
                            for (int aa = 0; aa < this->players_amt; aa++) {
                                if (playersAuction[aa] != -1) {
                                    winnerCount++;
                                }
                            }
                            if (winnerCount == 1 && someoneHasBid == true) {
                                std::cout << this->players[highestBidder].getPlayerName() << " won "
                                          << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                          << " for $" << bidAmount << std::endl;

                                //Following statements set Auction winner as owner, subtracts amount bidded from cash, ends turn...


                                //Set owner of property to Auction winner
                                this->board.getPropertySet()[this->players[this->player_turn].getPosition()].setOwner(
                                        this->players[highestBidder].getPlayer_num());
                                //Add owned properties to Auction winner
                                this->players[highestBidder].addProperty(
                                        this->board.getPropertySet()[this->players[this->player_turn].getPosition()]);
                                //Subtract bid amount from Auction winner cash
                                this->players[highestBidder].setCash(this->players[x].getCash() - bidAmount);


                                subsetVal = 0;
                                ownerSubsetVal = 0;
                                for (int i = 0; i <= board.getMaxSetID(); i++) {
                                    for (int j = 1; j < this->board.getSpaceCount(); j++) {
                                        if (board.getPropertySet()[j].getSetID() == i) {
                                            subsetVal++;
                                        }
                                    }
                                    for (int k = 0; k < (short) this->players[x].getUser_properties().size(); k++) {
                                        if (this->players[x].getUser_properties()[k].getSetID() == i) {
                                            ownerSubsetVal++;
                                        }
                                    }
                                    if (ownerSubsetVal == subsetVal) {
                                        this->players[x].getPropSetOwner()[i] = 1;
                                        this->players[x].setSetOwner(true);
                                    }
                                }

                                endAuction = true;
                                break;
                            }
                        }
                    }

                    if (roll->isDoubles() && this->players[this->player_turn].getRollCount() <
                                             this->getRulesClass().getMaxDoublesReRolls()) {
                        this->players[this->player_turn].setRoll(false);
                        this->players[this->player_turn].setRollCount(
                                this->players[this->player_turn].getRollCount() + 1);
                        endAuction = true;
                        break;
                    } else {
                        this->players[this->player_turn].setRoll(false);
                        this->setEnds_turn(true);
                        this->players[this->player_turn].setRollCount(0);
                        endAuction = true;
                        break;
                    }

                }


                else if (this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()
                         == -1 && this->players[this->player_turn].getCash() <
                                  this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice() && !this->rulesClass.isAuction()) {
                    // commment if they dont have enough $$
                    std::cout << this->players[this->player_turn].getPlayerName() << ", you don't have enough money to afford " << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << "." << std::endl;
                    std::cout << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << " costs $"
                              << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getPrice() << " but you only have $" << this->players[this->player_turn].getCash() << std::endl;
                    if (roll->isDoubles() && this->players[this->player_turn].getRollCount() <
                                             this->getRulesClass().getMaxDoublesReRolls()) {
                        this->players[this->player_turn].setRoll(false);
                        this->players[this->player_turn].setRollCount(
                                this->players[this->player_turn].getRollCount() + 1);
                        endAuction = true;
                        break;
                    } else {
                        this->players[this->player_turn].setRoll(false);
                        this->setEnds_turn(true);
                        this->players[this->player_turn].setRollCount(0);
                        endAuction = true;
                        break;
                    }


                }




                    // player lands on their own property //
                else if (this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner() == this->players[this->player_turn].getPlayer_num() ) {
                    std:: cout << this->players[this->player_turn].getPlayerName() << ", you landed on " << board.getPropertySet()[this->players[this->player_turn].getPosition()].getName()
                                << "which you already own" << std::endl;
                    if (roll->isDoubles()&&this->players[this->player_turn].getRollCount() < this->getRulesClass().getMaxDoublesReRolls()){
                        this->players[this->player_turn].setRoll(false);
                        this->players[this->player_turn].setRollCount(this->players[this->player_turn].getRollCount()+1);
                        break;
                    }
                    else {
                        this->players[this->player_turn].setRoll(false);
                        this->setEnds_turn(true);
                        this->players[this->player_turn].setRollCount(0);
                        break;
                    }
                }

                    // someone else owns the property //
                else if (this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner() != this->players[this->player_turn].getPlayer_num() &&
                         this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner() != -1 && this->players[this->player_turn].getPosition() != 0){

                    payRentSetID = this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getSetID();

                    for (int v = 0; v  <= this->board.getMaxSetID(); v++ ){
                        if (this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPropSetOwner()[payRentSetID] == 1){
                            ownsSubset = true;
                        }
                    }


                    if (ownsSubset && this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].isUpgradeOwner()){


                        if (this->players[this->player_turn].getCash() >= ((this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent_with_house() *
                                                                            static_cast<int>(pow(2,this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getHouses() -1)) ) +
                                                                           this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent_with_hotel())){
                            this->players[this->player_turn].setCash (this->players[this->player_turn].getCash() -
                                                                      ((this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent_with_house() *
                                                                        static_cast<int>(pow(2,this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getHouses() -1)) ) +
                                                                       this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent_with_hotel()));
                            this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].setCash(
                                    this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getCash() + ((this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent_with_house() *
                                                                                                                                                         static_cast<int>(pow(2,this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getHouses() -1)) ) +
                                                                                                                                                        this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent_with_hotel())) ;
                            std::cout << this->players[this->player_turn].getPlayerName() << " paid "
                                      <<  this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayerName()
                                      << "$" << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent()*getRulesClass().getProperty_set_multiplier() << " for landing on " <<
                                      this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << std::endl;
                            if (roll->isDoubles()&&this->players[this->player_turn].getRollCount() < this->getRulesClass().getMaxDoublesReRolls()){
                                this->players[this->player_turn].setRoll(false);
                                this->players[this->player_turn].setRollCount(this->players[this->player_turn].getRollCount()+1);
                                break;
                            }
                            else {
                                this->players[this->player_turn].setRoll(false);
                                this->setEnds_turn(true);
                                this->players[this->player_turn].setRollCount(0);
                                break;
                            }
                        }
                            // bankruptcy loop //
                        else{
                            std::cout << this->players[this->player_turn].getPlayerName() << " went bankrupt to " <<
                                      this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayerName()
                                      << " for landing on "  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << std::endl;

                            this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].setCash (
                                    this->players[this->player_turn].getCash()+
                                    this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getCash())  ; // adds money to owner of prop
                            this->players[this->player_turn].setCash(0); // takes cash from broke player sets to 0
                            this->players[this->player_turn].setPlayer_num (-1); // semantically removes player from game by setting to -1
                            for (uint i=0; i< this->players[this->player_turn].getUser_properties().size(); i++){
                                this->players[this->player_turn].getUser_properties()[i].setOwner (
                                        this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayer_num());
                                this->board.getPropertySet()[this->players[this->player_turn].getUser_properties()[i].getSpaceNum()].setOwner(
                                        this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayer_num());
                                this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].addProperty(
                                        this->players[this->player_turn].getUser_properties()[i]);

                            }
                            this->players[this->player_turn].getUser_properties().clear();
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            break;

                        }



                    }




                    else if (ownsSubset){
                        if (this->players[this->player_turn].getCash() >= this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent() *
                                                                          getRulesClass().getProperty_set_multiplier()) {
                            this->players[this->player_turn].setCash (this->players[this->player_turn].getCash() -
                                                                      this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent() *
                                                                      getRulesClass().getProperty_set_multiplier());
                            this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].setCash(
                                    this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent() *
                                    getRulesClass().getProperty_set_multiplier()+
                                    this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getCash());
                            std::cout << this->players[this->player_turn].getPlayerName() << " paid "
                                      <<  this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayerName()
                                      << "$" << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent()*getRulesClass().getProperty_set_multiplier() << " for landing on " <<
                                      this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << std::endl;
                            if (roll->isDoubles()&&this->players[this->player_turn].getRollCount() < this->getRulesClass().getMaxDoublesReRolls()){
                                this->players[this->player_turn].setRoll(false);
                                this->players[this->player_turn].setRollCount(this->players[this->player_turn].getRollCount()+1);
                                break;
                            }
                            else {
                                this->players[this->player_turn].setRoll(false);
                                this->setEnds_turn(true);
                                this->players[this->player_turn].setRollCount(0);
                                break;
                            }
                        }
                            // bankruptcy loop //
                        else{
                            std::cout << this->players[this->player_turn].getPlayerName() << " went bankrupt to " <<
                                      this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayerName()
                                      << " for landing on "  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << std::endl;

                            this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].setCash (
                                    this->players[this->player_turn].getCash()+
                                    this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getCash())  ; // adds money to owner of prop
                            this->players[this->player_turn].setCash(0); // takes cash from broke player sets to 0
                            this->players[this->player_turn].setPlayer_num (-1); // semantically removes player from game by setting to -1
                            for (uint i=0; i< this->players[this->player_turn].getUser_properties().size(); i++){
                                this->players[this->player_turn].getUser_properties()[i].setOwner (
                                        this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayer_num());
                                this->board.getPropertySet()[this->players[this->player_turn].getUser_properties()[i].getSpaceNum()].setOwner(
                                        this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayer_num());
                                this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].addProperty(
                                        this->players[this->player_turn].getUser_properties()[i]);

                            }
                            this->players[this->player_turn].getUser_properties().clear();
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            break;

                        }
                    }
                    else{
                        if (this->players[this->player_turn].getCash() >= this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent()) {

                            this->players[this->player_turn].setCash (this->players[this->player_turn].getCash() -
                                                                      this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent());
                            this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].setCash(
                                    this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent() +
                                    this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getCash());
                            std::cout << this->players[this->player_turn].getPlayerName() << " paid "
                                      << this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayerName()
                                      << "$" << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getRent() << " for landing on " <<
                                      this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << std::endl;
                            if (roll->isDoubles()&&this->players[this->player_turn].getRollCount() < this->getRulesClass().getMaxDoublesReRolls()){
                                this->players[this->player_turn].setRoll(false);
                                this->players[this->player_turn].setRollCount(this->players[this->player_turn].getRollCount()+1);
                                break;
                            }
                            else {
                                this->players[this->player_turn].setRoll(false);
                                this->setEnds_turn(true);
                                this->players[this->player_turn].setRollCount(0);
                                break;
                            }

                        }
                        else{
                            std::cout << this->players[this->player_turn].getPlayerName() << " went bankrupt to " <<
                                      this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayerName()
                                      << " for landing on "  << this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getName() << std::endl;

                            this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].setCash (
                                    this->players[this->player_turn].getCash()+
                                    this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getCash())  ; // adds money to owner of prop
                            this->players[this->player_turn].setCash(0); // takes cash from broke player sets to 0
                            this->players[this->player_turn].setPlayer_num (-1); // semantically removes player from game by setting to -1
                            for (uint i=0; i< this->players[this->player_turn].getUser_properties().size(); i++){
                                this->players[this->player_turn].getUser_properties()[i].setOwner (
                                        this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayer_num());
                                this->board.getPropertySet()[this->players[this->player_turn].getUser_properties()[i].getSpaceNum()].setOwner(
                                        this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].getPlayer_num());
                                this->players[this->board.getPropertySet()[this->players[this->player_turn].getPosition()].getOwner()].addProperty(
                                        this->players[this->player_turn].getUser_properties()[i]);
                            }
                            this->players[this->player_turn].getUser_properties().clear();
                            this->players[this->player_turn].setRoll(false);
                            this->setEnds_turn(true);
                            break;
                        }
                    }
                }

            case 2:
                if (this->players[this->player_turn].isSetOwner() && !this->MaxedOut){
                    std::cout<< "Which property do you want to upgrade?" <<std::endl;

                    // display available upgrades//

                    for (int i = 0; i <= board.getMaxSetID(); i++) {
                        subsetVal = 0;
                        for (int j = 1; j < this->board.getSpaceCount(); j++) {
                            if (board.getPropertySet()[j].getSetID() == i) {
                                subsetVal++;
                            }
                        }
                        this->subSetCount.push_back(subsetVal);
                    }


                    if (this->rulesClass.isBuild_houses_evenly()){
                        subsetVal = 0;
                        for (int i = 0; i <= this->board.getMaxSetID(); i++){
                            if (this->players[this->player_turn].getPropSetOwner()[i] == 1) {
                                for (int l = 1; l <  this->board.getSpaceCount()-subSetCount[i]; l++){
                                    if (this->board.getPropertySet()[l].getSetID() == i) {
                                        maxUpgrades = this->board.getPropertySet()[l].getHouses() + this->board.getPropertySet()[l].getHotels()*this->rulesClass.getHouses_before_hotels();
                                        evenlyBuilt = true;
                                        for (int j = 0; j< this->board.getSpaceCount(); j++) {
                                            if (this->board.getPropertySet()[j].getSetID() == j) {
                                                if (maxUpgrades < this->board.getPropertySet()[j].getHouses() +
                                                                  this->board.getPropertySet()[j].getHotels() *
                                                                  this->rulesClass.getHouses_before_hotels()) {
                                                    maxUpgrades = this->board.getPropertySet()[j].getHouses() +
                                                                  this->board.getPropertySet()[j].getHotels() *
                                                                  this->rulesClass.getHouses_before_hotels();
                                                    evenlyBuilt = false;
                                                } else if (maxUpgrades !=
                                                           this->board.getPropertySet()[j].getHouses() +
                                                           this->board.getPropertySet()[j].getHotels() *
                                                           this->rulesClass.getHouses_before_hotels()) {
                                                    evenlyBuilt = false;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                }
                                for (int x = 1; x < this->board.getSpaceCount(); x++){
                                    if ((this->board.getPropertySet()[x].getSetID() == i && ((this->board.getPropertySet()[x].getHouses()+
                                                                                             this->board.getPropertySet()[x].getHotels()*
                                                                                                     this->rulesClass.getHouses_before_hotels()) < maxUpgrades) && this->board.getPropertySet()[x].getOwner() == this->player_turn )
                                                                                        || (this->board.getPropertySet()[x].getSetID() == i && !this->players[this->player_turn].isUpgradeOwner())
                                                                                        || (this->board.getPropertySet()[x].getSetID() == i && subSetCount[i] == 1 && this->board.getPropertySet()[x].getOwner() == this->player_turn)
                                                                                        || (this->board.getPropertySet()[x].getSetID() == i && this->board.getPropertySet()[x].getHouses() == 0 && this->board.getPropertySet()[x].getOwner() == this->player_turn)
                                                                                        || (this->board.getPropertySet()[x].getSetID()== i && evenlyBuilt && this->players[this->player_turn].isUpgradeOwner())){



                                        this->monopoly.push_back(this->board.getPropertySet()[x]);
                                        std::cout << subsetVal << ". " << this->board.getPropertySet()[x].getName()
                                                  << " [$";
                                        if (this->board.getPropertySet()[x].getHouses() <
                                            this->rulesClass.getHouses_before_hotels()) {
                                            std::cout << this->board.getPropertySet()[x].getHouse_cost() << "]"
                                                      << std::endl;
                                        } else {
                                            std::cout << this->board.getPropertySet()[x].getHotel_cost() << "]"
                                                      << std::endl;
                                        }
                                        subsetVal++;
                                    }
                                }
                            }
                        }
                    }



                    else {
                        subsetVal = 0;
                        for (int i = 0; i <= this->board.getMaxSetID(); i++) {
                            if (this->players[this->player_turn].getPropSetOwner()[i] == 1) {
                                for (int j = 1; j < this->board.getSpaceCount(); j++) {
                                    if (this->board.getPropertySet()[j].getSetID() == i && this->board.getPropertySet()[j].getHotels() == 0) {
                                        this->monopoly.push_back(this->board.getPropertySet()[j]);
                                        std::cout << subsetVal << ". " << this->board.getPropertySet()[j].getName()
                                                  << " [$";
                                        if (this->board.getPropertySet()[j].getHouses() <
                                            this->rulesClass.getHouses_before_hotels()) {
                                            std::cout << this->board.getPropertySet()[j].getHouse_cost() << "]"
                                                      << std::endl;
                                        } else {
                                            std::cout << this->board.getPropertySet()[j].getHotel_cost() << "]"
                                                      << std::endl;
                                        }
                                        subsetVal++;
                                    }
                                }
                            }
                        }
                    }
                    std::cout << "Your choice: ";
                    std::cin >> upgradeChoice;
                    for (int l =0; l < subsetVal; l++){
                        if (upgradeChoice == l &&this->monopoly[l].getHouses() < this->rulesClass.getHouses_before_hotels() ){
                            if (this->players[this->player_turn].getCash() > this->monopoly[l].getHouse_cost() ){
                                for (int m = 0; m <  (short) this->players[this->player_turn].getUser_properties().size(); m++){
                                    if (this->monopoly[l].getSpaceNum() == this->players[this->player_turn].getUser_properties()[m].getSpaceNum()){
                                        this->players[this->player_turn].getUser_properties()[m].setHouses(this->players[this->player_turn].getUser_properties()[m].getHouses() +1);
                                        this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].setHouses(this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].getHouses()+1);
                                        this->players[this->player_turn].setCash(this->players[this->player_turn].getCash() - this->players[this->player_turn].getUser_properties()[m].getHouse_cost());
                                        this->players[this->player_turn].setUpgradeOwner(true);
                                    }
                                }
                            }
                            else{
                                std::cout << "You don't have enough money to purchase a house on this property" << std::endl;
                            }

                        }
                        else if (upgradeChoice == l && this->monopoly[l].getHouses() == this->rulesClass.getHouses_before_hotels() ){
                            if (this->players[this->player_turn].getCash() > this->monopoly[l].getHotel_cost() ){
                                for (int o = 0; o < (short) this->players[this->player_turn].getUser_properties().size(); o++){
                                    if (this->monopoly[l].getSpaceNum() == this->players[this->player_turn].getUser_properties()[o].getSpaceNum()){
                                        this->players[this->player_turn].getUser_properties()[o].setHouses(0);
                                        this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].setHouses(0);
                                        this->players[this->player_turn].getUser_properties()[o].setHotels(this->players[this->player_turn].getUser_properties()[o].getHotels() + 1);
                                        this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].setHotels(this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].getHotels()+1);
                                        this->players[this->player_turn].setCash(this->players[this->player_turn].getCash() - this->players[this->player_turn].getUser_properties()[o].getHotel_cost());
                                    }
                                }
                            }
                            else{
                                std::cout<< "You dont have enough money to purchase a hotel on this property" << std::endl;
                            }
                        }
                    }

                    while_val = 0;
                    for (int f = 0 ; f < (short) this->players[this->player_turn].getUser_properties().size(); f++){
                        if (this->players[this->player_turn].getUser_properties()[f].getHotels() != 1){
                            while_val++;
                        }
                    }
                    if (while_val == 0){
                        this->MaxedOut = true;
                    }


                    this->subSetCount.clear();
                    this->monopoly.clear();
                }
                else{
                    std::cout << "You don't have any properties that you can upgrade" << std::endl;
                }



                break;


            case 3:

                if (this->players[this->player_turn].isUpgradeOwner()){
                    std::cout<< "Which property do you want to downgrade?" <<std::endl;

                    // display available upgrades//
                    subsetVal = 0;
                    for (int i = 0; i <= this->board.getMaxSetID(); i++){
                        if (this->players[this->player_turn].getPropSetOwner()[i]==1){
                            for (int j = 0; j < this->board.getSpaceCount(); j++){
                                if (this->board.getPropertySet()[j].getSetID()==i) {
                                    if (this->board.getPropertySet()[j].getHouses() > 0 ||
                                        this->board.getPropertySet()[j].getHotels() > 0) {
                                        this->monopoly.push_back(this->board.getPropertySet()[j]);
                                        std::cout << subsetVal << ". " << this->board.getPropertySet()[j].getName()
                                                  << " [$";
                                        if (this->board.getPropertySet()[j].getHouses() <
                                            this->rulesClass.getHouses_before_hotels()) {
                                            std::cout << this->board.getPropertySet()[j].getHouse_cost() / 2 << "]"
                                                      << std::endl;
                                        } else {
                                            std::cout << this->board.getPropertySet()[j].getHotel_cost() / 2 << "]"
                                                      << std::endl;
                                        }
                                        subsetVal++;
                                    }
                                }
                            }
                        }
                    }
                    std::cout << "Your choice: ";
                    std::cin >> upgradeChoice;
                    for (int l =0; l < subsetVal; l++){
                        if (upgradeChoice == l &&this->monopoly[l].getHouses() > 0 ){
                            for (int m = 0; m < (short) this->players[this->player_turn].getUser_properties().size(); m++){
                                if (this->monopoly[l].getSpaceNum() == this->players[this->player_turn].getUser_properties()[m].getSpaceNum()){
                                    this->players[this->player_turn].getUser_properties()[m].setHouses(this->players[this->player_turn].getUser_properties()[m].getHouses() - 1);
                                    this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].setHouses(this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].getHouses() - 1);
                                    this->players[this->player_turn].setCash(this->players[this->player_turn].getCash()  + this->players[this->player_turn].getUser_properties()[m].getHouse_cost()/2);
                                }
                            }
                        }
                        else if (upgradeChoice == l && this->monopoly[l].getHotels() > 0 ){
                            for (int o = 0; o < (short) this->players[this->player_turn].getUser_properties().size(); o++){
                                if (this->monopoly[l].getSpaceNum() == this->players[this->player_turn].getUser_properties()[o].getSpaceNum()){
                                    this->players[this->player_turn].getUser_properties()[o].setHotels(this->players[this->player_turn].getUser_properties()[o].getHotels() - 1);
                                    this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].setHotels(this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].getHotels() - 1);
                                    this->players[this->player_turn].setCash(this->players[this->player_turn].getCash() + this->players[this->player_turn].getUser_properties()[o].getHotel_cost()/2);
                                    this->players[this->player_turn].getUser_properties()[o].setHouses(this->rulesClass.getHouses_before_hotels());
                                    this->board.getPropertySet()[this->monopoly[l].getSpaceNum()].setHouses(this->rulesClass.getHouses_before_hotels());
                                }
                            }
                        }
                    }

                    sellout = 0;
                    for (int p = 0; p < (short) this->players[this->player_turn].getUser_properties().size(); p++){
                        if (this->players[this->player_turn].getUser_properties()[p].getHouses() > 0 || this->players[this->player_turn].getUser_properties()[p].getHotels()> 0 ){
                            sellout++;
                        }
                    }

                    if (sellout == 0){
                        this->players[this->player_turn].setUpgradeOwner(false);
                    }


                    for (int f = 0 ; f < (short) this->players[this->player_turn].getUser_properties().size(); f++){
                        if (this->players[this->player_turn].getUser_properties()[f].getHotels() != 1){
                            this->MaxedOut = false;
                        }
                    }


                    this->monopoly.clear();
                }
                else{
                    std::cout << "You don't have any upgrades that you can sell" << std::endl;
                }

                break;



            case 4:

                this->players[this->player_turn].setCash(0);

                for (int l = 0; l< this->board.getSpaceCount(); l++){
                    for (uint i=0; i< this->players[this->player_turn].getUser_properties().size(); i++){
                        if (this->board.getPropertySet()[l].getOwner() == this->players[this->player_turn].getUser_properties()[i].getOwner()  ){
                            this->board.getPropertySet()[l].setOwner(-1);
                            this->board.getPropertySet()[l].setHouses(0);
                            this->board.getPropertySet()[l].setHotels(0);
                        }

                    }
                }
                this->players[this->player_turn].setPlayer_num(-1);
                this->players[this->player_turn].getUser_properties().clear();

                this->setEnds_turn(true);
                this->players[this->player_turn].setRoll(false);
                break;
        }
    }


}




int Gamestate::getPlayers_amt() const {
    return players_amt;
}

void Gamestate::setPlayers_amt(int players_amt) {
    Gamestate::players_amt = players_amt;
}

int Gamestate::getPlayer_turn () const{
    return player_turn;
}

void Gamestate::setPlayer_turn(int player_turn) {
    Gamestate::player_turn = player_turn;
}






int Gamestate::getTurnCount() const {
    return turnCount;
}

void Gamestate::setTurnCount(int turnCount) {
    Gamestate::turnCount = turnCount;
}

void Gamestate::get_move(int playernumber){

    this->setEnds_turn(false);
    std::cout<< this->players[this->player_turn].getPlayerName() << " please enter your move" <<  std::endl;
    // if (!players[playernumber].isRoll()){
    std::cout << "1 to roll dice" << std::endl;
    //std::cout << "2: Inspect Player" << std::endl;
    std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
    std::cout << "3 to sell a house or hotel" <<std::endl;
    std::cout << "4 to leave the game" << std::endl;
    std::cout << "Your move: " << std::endl;
    // }
    /* else{
         std::cout << "1: End Turn" << std::endl;
         std::cout << "2: Inspect Player" << std::endl;
         std::cout << "3: Leave Game" << std::endl;
         std::cout << "Your action: " << std::endl;
     }*/

    int choiceVar;
    std::cin >> choiceVar;
    this->setChoice(choiceVar);

}

DiceRoller *Gamestate::getRoller() const {
    return roller;
}

void Gamestate::setRoller(DiceRoller *roller) {
    Gamestate::roller = roller;
}

bool Gamestate::isEnds_turn() const {
    return ends_turn;
}

void Gamestate::setEnds_turn(bool ends_turn) {
    Gamestate::ends_turn = ends_turn;
}

int Gamestate::getChoice() const {
    return choice;
}

void Gamestate::setChoice(int choice) {
    Gamestate::choice = choice;
}

Rules Gamestate::getRulesClass() const {
    return rulesClass;
}

void Gamestate::setRulesClass(Rules rulesClass) {
    Gamestate::rulesClass = rulesClass;
}


std::vector<Player> &Gamestate::getPlayers(){
    return players;

}

void Gamestate::setPlayer( std::vector<Player> &player) {
    Gamestate::players = player;
}

Board Gamestate::getBoard () {
    return board;
}

void Gamestate::setBoard(Board board) {
    Gamestate::board = board;
}
