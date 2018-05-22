//
// Created by Adam Levin on 2/26/18.
//

#include "Gamestate.h"
#include <vector>



void Monopoly::Gamestate::setup(char* rulefile, char* boardfile) {
    // generate rules and board via smartpointer and setup functions //

    rules = std::make_unique<Monopoly::Rules>();
    bigboard = std::make_unique<Monopoly::Board>();
    rules->ruleSetup(rulefile);
    bigboard->BoardSetup(boardfile);
    // generate players and other gamestate information //
    int tempPlayeramt;
    std::cout << "Enter how many players will be playing: ";
    std::cin >> tempPlayeramt;

    setTurnCount(0);
    setPlayer_turn(0);
    setPlayers_amt(tempPlayeramt);

    std::string tempname;
    for (int i=0; i<getPlayers_amt(); i++) {
        players.push_back(std::make_unique<Monopoly::Player>());
        std::cout<< "Enter the name of player " << i + 1 << ": ";
        std::cin>> tempname;
        players[i]->setPlayerName(tempname);
        players[i]->setCash(rules->getStarting_cash());
        players[i]->setNetWorth(rules->getStarting_cash());
        players[i]->setPosition(0);
        players[i]->setPlayer_num(i);
        players[i]->setRollCount(0);
        players[i]->setPropSetOwner(std::vector<int>((uint)bigboard->getMaxSetID() +1, -1));
        players[i]->setSetOwner(false);
        players[i]->setPropertyMaxed(false);
        players[i]->setUpgradeOwner(false);
        players[i]->setGoCash(bigboard->getPassGoCash());
        players[i]->setGoMultiplier(rules->getGo_multiplier());
        players[i]->setAuction(rules->isAuction());
        players[i]->setNeedToPay(false);
        players[i]->setPlayerToPay(-1);
        players[i]->setCashToPay(0);
        players[i]->setBrokeToPlayer(false);
        players[i]->setSpacePaid("");
        players[i]->setPropertySetMultiplier(rules->getProperty_set_multiplier());
        players[i]->setTurnsInJail(0);
        players[i]->setAuctionTurn(false);
        players[i]->setPayFP(0);
        players[i]->setJustVisiting(true);
        players[i]->setFirstTurnInJail(false);
        players[i]->setBankrupt(false);
        players[i]->setHousesb4hotels(rules->getHouses_before_hotels());
        players[i]->setHasDowngraded(false);
        players[i]->setFreeParking(rules->isFreeparking());
        players[i]->setSentToJail(false);
        players[i]->setJustPurchased(false);
        players[i]->setSubsetAmt(std::vector<int>((uint)bigboard->getMaxSetID()+1, -1));
    }
}

bool Monopoly::Gamestate::isGameOver(){
    bool game_over = false;

    if (turnCount >= rules->getTurn_limit() && rules->getTurn_limit()!=-1){
        game_over = true;
    }

    int players_remaining = 0;
    for (int i = 0; i< players_amt; i++){
        if (players[i]->getPlayer_num() != -1) {
            players_remaining = players_remaining + 1;
        }

    }
    if (players_remaining <= rules->getPlayer_endgame()){
        game_over = true;
    }

    return game_over;
}

void Monopoly::Gamestate::declare_winners(){
    std::vector<std::string> finalWinners;
    int maxPrice = 0;
    int playerwinners[getPlayers_amt()];
    for (int i = 0; i < getPlayers_amt(); i++){
        if (players[i]->getPlayer_num() != -1) {
            playerwinners[i] = players[i]->getCash();
            for ( int j = 0; j < (unsigned short) players[i]->getUser_properties().size(); j++){
                playerwinners[i] += players[i]->getUser_properties()[j].getPrice();
                playerwinners[i] += players[i]->getUser_properties()[j].getHouses()*players[i]->getUser_properties()[j].getHouseCost();
                playerwinners[i] +=  players[i]->getUser_properties()[j].getHotels()*players[i]->getUser_properties()[j].getHotelCost();
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
    for (int k = 0; k< getPlayers_amt(); k++){
        if (playerwinners[k] == maxPrice){
            finalWinners.push_back(players[k]->getPlayerName());
        }
    }
    std::cout << "The winners are " << std::endl;
    for (uint l = 0; l < finalWinners.size(); l++) {
        std::cout << finalWinners[l] << std::endl;
    }
}

void Monopoly::Gamestate::display_game_state(){


    int placecount;

    std::cout<< "Space Number | Space Name | Owner  | Upgrades | Players" << std::endl;
    for (int l = 0; l< bigboard->getSpaceCount(); l++){
        bigboard->getboard()[l]->display();
        placecount = 0;
        for (int k = 0 ; k< getPlayers_amt(); k++){
            if (players[k]->getPosition() == l && players[k]->getPlayer_num() != -1){
                if (placecount >= 1 ){
                    std::cout << ", ";
                }
                std::cout <<"["<< players[k]->getPlayerName() << " : $";
                std::cout << players[k]->getCash() << "]";
                placecount = placecount + 1;
            }

        }
        std::cout << std::endl;
    }

}
void Monopoly::Gamestate::change_turn() {



    for (int i=0; i<getPlayers_amt(); i++){

        if (player_turn <= getPlayers_amt() - 2 &&
            (players[player_turn + 1]->getPlayer_num() != -1)) {
            setPlayer_turn(player_turn+1); // increment function
            break;
        } else if (player_turn == getPlayers_amt() - 1 && players[0]->getPlayer_num() != -1) {
            setPlayer_turn(0);

            break;
        }
        else{
            setPlayer_turn(player_turn+1);
        }
    }

    //if (getPlayer_turn() == 0){
        setTurnCount(getTurnCount() + 1);
    //}

}

void Monopoly::Gamestate::jailCheck() {

    //jail = dynamic_cast<Jail*>(bigboard->getboard()[players[player_turn]->getPosition()]);
    // they have run out of turns in jail and will trigger the pay to get out option //
    if (!players[player_turn]->isJustVisiting()&& players[player_turn]->getTurnsInJail() == 0){
        bigboard->getboard()[players[player_turn]->getPosition()]->activate(*players[player_turn]);
        // bankrupt in jail things or bankrupt in paybank //
        if (players[player_turn]->isBankrupt()) {
            players[player_turn]->setCash(0);
            for (int l = 0; l < bigboard->getSpaceCount(); l++) {
                for (uint i = 0; i < (unsigned short) players[player_turn]->getUser_properties().size(); i++) {
                    if (bigboard->getboard()[l]->getSpaceNum() ==
                        players[player_turn]->getUser_properties()[i].getSpaceNum()) {
                        Monopoly::Property *tempProp;
                        tempProp = dynamic_cast<Property *>(bigboard->getboard()[i].get());
                        //dynamic_cast<Property*>(bigboard->getboard()[j])->setOwner(players[player_turn]->getPlayerToPay());
                        tempProp->setOwner(-1);
                        tempProp->setHouses(0);
                        tempProp->setHotels(0);
                        //bigboard->getboard()[i] = tempProp;
                    }

                }
            }
            players[player_turn]->setPlayer_num(-1);
            players[player_turn]->getUser_properties().clear();
            setEnds_turn(true);
        }
        else {
            if (players[player_turn]->getPayFP() > 0) {
                bigboard->setTotalFPCash(bigboard->getTotalFPCash() +
                                         players[player_turn]->getPayFP());
            } else {
                bigboard->setTotalFPCash(0);

            }

            for (int i = 0; i < bigboard->getSpaceCount(); i++) {
                Monopoly::FreeParking *fp;
                fp = dynamic_cast<FreeParking *>(bigboard->getboard()[i].get());
                if (fp != NULL) {
                    fp->setFpCash((bigboard->getTotalFPCash()));
                    //bigboard->getboard()[i] = fp;
                }
            }
            players[player_turn]->setPayFP(0);
            setEnds_turn(false);
        }
    }
    // if they have enough money to pay the fee and want to leave early //
    else if (!players[player_turn]->isJustVisiting()&& players[player_turn]->getTurnsInJail() > 0) {
        auto *jail = static_cast<Jail *>(bigboard->getboard()[players[player_turn]->getPosition()].get());
        if (players[player_turn]->getCash() >= jail->getFeeToLeave()) {
            std::cout << players[player_turn]->getPlayerName() << " you are in jail for "
                      << players[player_turn]->getTurnsInJail() << "turns." << std::endl;
            std::cout << "Would you like to pay $" << jail->getFeeToLeave() << " to leave jail early?" << std::endl;
            std::cout << "y for yes and n for no:";
            char jailpay;
            std::cin >> jailpay;
            if (jailpay == 'y') {
                players[player_turn]->setCash(players[player_turn]->getCash() - jail->getFeeToLeave());
                players[player_turn]->setJustVisiting(true);
            }
        }
        else {
            std::cout << players[player_turn]->getPlayerName() << " you are in jail for "
                      << players[player_turn]->getTurnsInJail() << "turns." << std::endl;
        }
        setEnds_turn(false);
    }
    else{
        setEnds_turn(false);
        // DO NOTHING THEY NOT LOCKED UP BRUH //
    }

}

void Monopoly::Gamestate::get_move(){

    std::cout<< players[player_turn]->getPlayerName() << " please enter your move" <<  std::endl;
    std::cout << "1 to roll dice" << std::endl;
    std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
    std::cout << "3 to sell a house or hotel" <<std::endl;
    std::cout << "4 to leave the game" << std::endl;
    std::cout << "Your move: " << std::endl;
    int choiceVar;
    std::cin >> choiceVar;
    setChoice(choiceVar);

}

void Monopoly::Gamestate::make_move(DiceRoller *roll) {
    if (!isEnds_turn()) {
        int move_num = 0;
        int temp_pos = 0;
        int while_val = 0;
        int subsetVal = 0;
        int ownerSubsetVal = 0;
        int bidAmount = 0;
        bool someoneHasBid = false;
        bool endAuction = false;
        int userBid = 0;
        int tempNoBidder = 0;
        int highestBidder = 0;
        int auctionCount = 0;
        int winnerCount = 0;
        int downGradeChoice = 0;
        int increment;
        int maxprop;
        int upgradeChoice = 0;

        switch (getChoice()) {
            case 1:
                if (!players[player_turn]->isJustVisiting()) {
                    std::cout << players[player_turn]->getPlayerName() << ", ";
                    move_num = roll->dice_roll();
                    std::cout << "you rolled a " << move_num << std::endl;
                    if (roll->isDoubles()) {
                        std::cout << "You broke out with doubles!!" << std::endl;
                        temp_pos = players[player_turn]->getPosition() + move_num;
                        if (temp_pos >= bigboard->getSpaceCount()) {
                            // this if statements and its nested branches represent passing or landing on go
                            while (temp_pos > bigboard->getSpaceCount() - 1) {
                                temp_pos -= bigboard->getSpaceCount();
                                while_val++;
                            }
                            if (while_val > 0 && temp_pos == 0) {
                                players[player_turn]->setCash(players[player_turn]->getCash() +
                                                                          (bigboard->getPassGoCash() *
                                                                           (while_val - 1)));
                                // gospace activate //
                                bigboard->getboard()[0]->activate(*players[player_turn]);

                                players[player_turn]->setPosition(temp_pos);

                                if (roll->isDoubles() &&
                                    players[player_turn]->getRollCount() <
                                    rules->getMaxDoublesReRolls()) {
                                    players[player_turn]->setRollCount(
                                            players[player_turn]->getRollCount() + 1);
                                    break;
                                } else {
                                    setEnds_turn(true);
                                    players[player_turn]->setRollCount(0);
                                    break;
                                }
                            } else if (while_val > 0 && temp_pos != 0) {
                                players[player_turn]->setCash(players[player_turn]->getCash() +
                                                                          (bigboard->getPassGoCash() *
                                                                           (while_val)));
                                players[player_turn]->setPosition(temp_pos);
                            }

                            if (while_val == 0 && players[player_turn]->getPosition() == 0) {
                                bigboard->getboard()[0]->activate(*players[player_turn]);
                                players[player_turn]->setPosition(temp_pos);
                                if (roll->isDoubles() &&
                                    players[player_turn]->getRollCount() <
                                    rules->getMaxDoublesReRolls()) {
                                    players[player_turn]->setRollCount(
                                            players[player_turn]->getRollCount() + 1);
                                    break;
                                } else {
                                    setEnds_turn(true);
                                    players[player_turn]->setRollCount(0);
                                    break;
                                }
                            }

                        } else {
                            players[player_turn]->setPosition(temp_pos);

                        }
                    } else {
                        std::cout << "You are still stuck in jail" << std::endl;
                    }

                } else {
                    std::cout << players[player_turn]->getPlayerName() << ", ";
                    move_num = roll->dice_roll();
                    std::cout << "you rolled a " << move_num << std::endl;
                    temp_pos = players[player_turn]->getPosition() + move_num;
                    if (temp_pos >= bigboard->getSpaceCount()) {
                        // this if statements and its nested branches represent passing or landing on go
                        while (temp_pos > bigboard->getSpaceCount() - 1) {
                            temp_pos -= bigboard->getSpaceCount();
                            while_val++;
                        }
                        if (while_val > 0 && temp_pos == 0) {
                            players[player_turn]->setCash(players[player_turn]->getCash() +
                                                                      (bigboard->getPassGoCash() *
                                                                       (while_val - 1)));
                            // gospace activate //
                            bigboard->getboard()[0]->activate(*players[player_turn]);

                            players[player_turn]->setPosition(temp_pos);

                            if (roll->isDoubles() &&
                                players[player_turn]->getRollCount() <
                                rules->getMaxDoublesReRolls()) {
                                players[player_turn]->setRollCount(
                                        players[player_turn]->getRollCount() + 1);
                                break;
                            } else {
                                setEnds_turn(true);
                                players[player_turn]->setRollCount(0);
                                break;
                            }
                        } else if (while_val > 0 && temp_pos != 0) {
                            players[player_turn]->setCash(players[player_turn]->getCash() +
                                                                      (bigboard->getPassGoCash() * (while_val)));
                            players[player_turn]->setPosition(temp_pos);
                        }

                        if (while_val == 0 && players[player_turn]->getPosition() == 0) {
                            bigboard->getboard()[0]->activate(*players[player_turn]);
                            players[player_turn]->setPosition(temp_pos);
                            if (roll->isDoubles() &&
                                players[player_turn]->getRollCount() <
                                rules->getMaxDoublesReRolls()) {
                                players[player_turn]->setRollCount(
                                        players[player_turn]->getRollCount() + 1);
                                break;
                            } else {
                                setEnds_turn(true);
                                players[player_turn]->setRollCount(0);
                                break;
                            }
                        }

                    } else {
                        players[player_turn]->setPosition(temp_pos);

                    }
                }


                // ACTIVAAAAAAAAAAAAAAAAAAAATE //
                bigboard->getboard()[players[player_turn]->getPosition()]->activate(
                        *players[player_turn]);
                // AFTER ACTIVAAAAATE       //


                // if just purchased a property //

                if (players[player_turn]->isJustPurchased()) {
                    // property set owner check //
                    for (int i = 0; i <= bigboard->getMaxSetID(); i++) {
                        subsetVal = 0;
                        ownerSubsetVal = 0;
                        for (int j = 1; j < bigboard->getSpaceCount(); j++) {
                            Monopoly::Property *setProp;
                            setProp = dynamic_cast<Property *>(bigboard->getboard()[j].get());
                            if (setProp != NULL ){
                                if (setProp->getSetID() == i) {
                                    subsetVal++;
                                }
                            }
                        }
                        for (int k = 0;
                             k < (short) players[player_turn]->getUser_properties().size(); k++) {
                            if (players[player_turn]->getUser_properties()[k].getSetID() == i) {
                                ownerSubsetVal++;
                            }
                        }
                        if (ownerSubsetVal == subsetVal) {
                            for (int j = 1; j < bigboard->getSpaceCount(); j++) {
                                Monopoly::Property *setProp;
                                setProp = dynamic_cast<Property *>(bigboard->getboard()[j].get());
                                if (setProp != NULL ){
                                    if (setProp->getSetID() == i) {
                                        setProp->setPropertySet(true);
                                    }
                                }
                            }
                            for (int k = 0;
                                 k < (short) players[player_turn]->getUser_properties().size(); k++) {
                                if (players[player_turn]->getUser_properties()[k].getSetID() == i) {
                                    players[player_turn]->getUser_properties()[k].setPropertySet(true);
                                }
                            }
                            players[player_turn]->getPropSetOwner()[i] = 1;
                            players[player_turn]->getSubsetAmt()[i] = subsetVal;
                            players[player_turn]->setSetOwner(true);
                        }
                    }
                    if (roll->isDoubles() &&
                        players[player_turn]->getRollCount() < rules->getMaxDoublesReRolls()) {
                        players[player_turn]->setRollCount(
                                players[player_turn]->getRollCount() + 1);
                        break;
                    } else {
                        setEnds_turn(true);
                        players[player_turn]->setRollCount(0);
                        break;
                    }
                }


                // sent to jail things //
                if (players[player_turn]->isSentToJail()) {
                    Monopoly::Jail *jail;
                    jail = dynamic_cast<Jail *>(bigboard->getboard()[players[player_turn]->getPosition()].get());
                    std::cout << players[player_turn]->getPlayerName() << ", you were sent to ";
                    std::cout << jail->getSpaceName() << " for " << jail->getTotalTurns() << "turns" << std::endl;
                    setEnds_turn(true);
                    players[player_turn]->setRollCount(0);
                    bigboard->getboard()[players[player_turn]->getPosition()]->activate(
                            *players[player_turn]);
                    break;
                }

                // bankrupt in jail things or bankrupt in paybank //
                if (players[player_turn]->isBankrupt()) {
                    players[player_turn]->setCash(0);
                    for (int l = 0; l < bigboard->getSpaceCount(); l++) {
                        for (uint i = 0; i < (unsigned short) players[player_turn]->getUser_properties().size(); i++) {
                            if (bigboard->getboard()[l]->getSpaceNum() ==
                                players[player_turn]->getUser_properties()[i].getSpaceNum()) {
                                Monopoly::Property *tempProp;
                                tempProp = dynamic_cast<Property *>(bigboard->getboard()[i].get());
                                //dynamic_cast<Property*>(bigboard->getboard()[j])->setOwner(players[player_turn]->getPlayerToPay());
                                tempProp->setOwner(-1);
                                tempProp->setHouses(0);
                                tempProp->setHotels(0);
                                //bigboard->getboard()[i] = tempProp;
                            }

                        }
                    }
                    players[player_turn]->setPlayer_num(-1);
                    players[player_turn]->getUser_properties().clear();
                    setEnds_turn(true);
                    break;
                }

                // after hitting pay to bank and freeparking is on //
                if (players[player_turn]->getPayFP() != 0 && rules->isFreeparking()) {
                    if (players[player_turn]->getPayFP() > 0){
                        bigboard->setTotalFPCash(bigboard->getTotalFPCash() +
                                players[player_turn]->getPayFP());
                    }
                    else{bigboard->setTotalFPCash(0);

                    }

                    for (int i = 0; i < bigboard->getSpaceCount(); i++) {
                        Monopoly::FreeParking *fp;
                        fp = dynamic_cast<FreeParking *>(bigboard->getboard()[i].get());
                        if (fp != NULL) {
                            fp->setFpCash((bigboard->getTotalFPCash()));
                            //bigboard->getboard()[i] = fp;
                        }
                    }
                    players[player_turn]->setPayFP(0);
                    if (roll->isDoubles() &&
                        players[player_turn]->getRollCount() < rules->getMaxDoublesReRolls()) {
                        players[player_turn]->setRollCount(
                                players[player_turn]->getRollCount() + 1);
                        break;
                    } else {
                        setEnds_turn(true);
                        players[player_turn]->setRollCount(0);
                        break;
                    }
                }

                // after hitting paybank and freeparking is off //
                if (players[player_turn]->getPayFP() > 0 && !rules->isFreeparking()) {
                    players[player_turn]->setPayFP(0);
                    if (roll->isDoubles() &&
                        players[player_turn]->getRollCount() < rules->getMaxDoublesReRolls()) {
                        players[player_turn]->setRollCount(
                                players[player_turn]->getRollCount() + 1);
                        break;
                    } else {
                        setEnds_turn(true);
                        players[player_turn]->setRollCount(0);
                        break;
                    }
                }

                // after hitting a freeParking space //
                if (players[player_turn]->getPayFP() <
                    0) {   // basically negative paying free parking is getting straight cash from free parking
                    bigboard->setTotalFPCash(
                            players[player_turn]->getPayFP() + bigboard->getTotalFPCash());
                    for (int i = 0; i < bigboard->getSpaceCount(); i++) {
                        if (bigboard->getboard()[i]->getSpaceType() == "FreeParking") {
                            Monopoly::FreeParking *fp;
                            fp = dynamic_cast<FreeParking *>(bigboard->getboard()[i].get());
                            fp->setFpCash(fp->getFpCash() +
                                          (bigboard->getTotalFPCash() / bigboard->getFPspaceCount()));
                            //bigboard->getboard()[i] = fp;
                        }
                    }
                    players[player_turn]->setPayFP(0);
                    if (roll->isDoubles() &&
                        players[player_turn]->getRollCount() < rules->getMaxDoublesReRolls()) {
                        players[player_turn]->setRollCount(
                                players[player_turn]->getRollCount() + 1);
                        break;
                    } else {
                        setEnds_turn(true);
                        players[player_turn]->setRollCount(0);
                        break;
                    }
                }


                // pay rent to another player and not broke //

                if (players[player_turn]->isNeedToPay() &&
                    !players[player_turn]->isBrokeToPlayer()) {

                    players[players[player_turn]->getPlayerToPay()]->setCash(
                            players[player_turn]->getCashToPay()
                            + players[players[player_turn]->getPlayerToPay()]->getCash());

                    std::cout << players[player_turn]->getPlayerName() << " paid "
                              << players[players[player_turn]->getPlayerToPay()]->getPlayerName()
                              << "$" << players[player_turn]->getCashToPay() << " for landing on " <<
                              players[player_turn]->getSpacePaid()
                              << std::endl;

                    players[player_turn]->setNeedToPay(false);
                    if (roll->isDoubles() &&
                        players[player_turn]->getRollCount() < rules->getMaxDoublesReRolls()) {
                        players[player_turn]->setRollCount(
                                players[player_turn]->getRollCount() + 1);
                        break;
                    } else {
                        setEnds_turn(true);
                        players[player_turn]->setRollCount(0);
                        break;
                    }

                }

                    // broke paying rent to another player

                else if (players[player_turn]->isNeedToPay() &&
                         players[player_turn]->isBrokeToPlayer()) {

                    players[players[player_turn]->getPlayerToPay()]->setCash(
                            players[player_turn]->getCashToPay()
                            + players[players[player_turn]->getPlayerToPay()]->getCash());


                    std::cout << players[player_turn]->getPlayerName() << " went bankrupt to "
                              << players[players[player_turn]->getPlayerToPay()]->getPlayerName()
                              << "$" << players[player_turn]->getCashToPay() << " for landing on " <<
                              players[player_turn]->getSpacePaid()
                              << std::endl;

                    for (int i = 0; i < (short) players[player_turn]->getUser_properties().size(); i++) {
                        for (int j = 0; j < bigboard->getSpaceCount(); j++) {
                            if (bigboard->getboard()[j]->getSpaceNum() ==
                                players[player_turn]->getUser_properties()[i].getSpaceNum()) {
                                Monopoly::Property *tempProp;
                                tempProp = static_cast<Property *>(bigboard->getboard()[j].get());
                                //dynamic_cast<Property*>(bigboard->getboard()[j])->setOwner(players[player_turn]->getPlayerToPay());
                                tempProp->setOwner(players[player_turn]->getPlayerToPay());
                                tempProp->setHouses(0);
                                tempProp->setHotels(0);
                                Monopoly::Property tempProp2(*tempProp);
                                //tempProp2.propertyCopy(*tempProp);
                                players[players[player_turn]->getPlayerToPay()]->getUser_properties().push_back(tempProp2);
                                //bigboard->getboard()[j] = tempProp;
                            }
                        }
                       // players[players[player_turn]->getPlayerToPay()]->getUser_properties()[i].setOwner(players[player_turn]->getPlayerToPay());
                    }
                    players[player_turn]->getUser_properties().clear();
                    setEnds_turn(true);
                    // property set owner check //
                    for (int i = 0; i <= bigboard->getMaxSetID(); i++) {
                        subsetVal = 0;
                        ownerSubsetVal = 0;
                        for (int j = 1; j < bigboard->getSpaceCount(); j++) {
                            Monopoly::Property *setProp;
                            setProp = dynamic_cast<Property *>(bigboard->getboard()[j].get());
                            if (setProp != NULL ){
                                if (setProp->getSetID() == i) {
                                    subsetVal++;
                                }
                            }
                        }
                        for (int k = 0; k <
                                        (short) players[players[player_turn]->getPlayerToPay()]->getUser_properties().size(); k++) {
                            if (players[players[player_turn]->getPlayerToPay()]->getUser_properties()[k].getSetID() ==
                                i) {
                                ownerSubsetVal++;
                            }
                        }
                        if (ownerSubsetVal == subsetVal) {
                            for (int j = 1; j < bigboard->getSpaceCount(); j++) {
                                Monopoly::Property *setProp;
                                setProp = dynamic_cast<Property *>(bigboard->getboard()[j].get());
                                if (setProp != NULL ){
                                    if (setProp->getSetID() == i) {
                                        setProp->setPropertySet(true);
                                    }
                                }
                            }
                            for (int k = 0;
                                 k < (short)players[players[player_turn]->getPlayerToPay()]->getUser_properties().size(); k++) {
                                if (players[players[player_turn]->getPlayerToPay()]->getUser_properties()[k].getSetID() == i) {
                                    players[players[player_turn]->getPlayerToPay()]->getUser_properties()[k].setPropertySet(true);
                                }
                            }
                            players[player_turn]->getPropSetOwner()[i] = 1;
                            players[player_turn]->getSubsetAmt()[i] = subsetVal;
                            players[player_turn]->setSetOwner(true);
                        }
                    }
                    break;
                }
                // auction branch //




                if (players[player_turn]->isAuctionTurn()) {

                    userBid = 0;
                    tempNoBidder = 0; //iterates if no one bids
                    //tempNoBidder != (short) tempPlayersInAuction.size()
                    std::vector<int> playersAuction((uint) getPlayers_amt());
                    for (int q = 0; q < getPlayers_amt(); q++) {
                        playersAuction[q] = q;
                    }

                    std::cout << "Starting the auction for "
                              << bigboard->getboard()[players[player_turn]->getPosition()]->getSpaceName()
                              << std::endl;
                    bidAmount = 1;
                    someoneHasBid = false;
                    while (!endAuction) {
                        for (int x = 0; x < getPlayers_amt(); x++) {
                            if (bidAmount == 1) {
                                std::cout << "No one has bid on "
                                          << bigboard->getboard()[players[player_turn]->getPosition()]->getSpaceName()
                                          << " [$ "
                                          << players[player_turn]->getAuctionPropertyPrice() << "] yet"
                                          << std::endl;
                                std::cout << players[x]->getPlayerName()
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
                                for (int w = 0; w < players_amt; w++) {

                                    if (playersAuction[w] != -1) {
                                        auctionCount++;
                                        break;

                                    }
                                }
                                if (auctionCount == 0) {
                                    std::cout << "No one decided to purchase "
                                              << bigboard->getboard()[players[player_turn]->getPosition()]->getSpaceName()
                                              << std::endl;
                                    endAuction = true;
                                    break;
                                }
                            }
                            if (bidAmount > 1 && playersAuction[x] != -1) {
                                std::cout << "The current bid for "
                                          << bigboard->getboard()[players[player_turn]->getPosition()]->getSpaceName()
                                          <<
                                          " [$ "
                                          << players[player_turn]->getAuctionPropertyPrice()
                                          << "] is $" << bidAmount << "by "
                                          << players[highestBidder]->getPlayerName()
                                          << std::endl;
                                std::cout << players[x]->getPlayerName()
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
                            for (int aa = 0; aa < players_amt; aa++) {
                                if (playersAuction[aa] != -1) {
                                    winnerCount++;
                                }
                            }
                            if (winnerCount == 1 && someoneHasBid) {
                                std::cout << players[highestBidder]->getPlayerName() << " won "
                                          << bigboard->getboard()[players[player_turn]->getPosition()]->getSpaceName()
                                          << " for $" << bidAmount << std::endl;
                                //Set owner of property to Auction winner
                                Monopoly::Property *tempProp;
                                tempProp = static_cast<Property *>(bigboard->getboard()[players[player_turn]->getPosition()].get());
                                tempProp->setOwner(players[highestBidder]->getPlayer_num());
                                tempProp->setPropertyOwnerName(players[highestBidder]->getPlayerName());
                                //bigboard->getboard()[players[player_turn]->getPosition()] = tempProp;
                                Monopoly::Property tempProp2(*tempProp);
                                //tempProp2.propertyCopy(*tempProp);
                                players[highestBidder]->getUser_properties().push_back(tempProp2);
                                players[highestBidder]->setCash(
                                        players[highestBidder]->getCash() - bidAmount);
                                players[player_turn]->setAuctionTurn(false);
                                endAuction = true;
                                break;
                            }
                        }
                    }
                    // property set owner check //
                    for (int i = 0; i <= bigboard->getMaxSetID(); i++) {
                        subsetVal = 0;
                        ownerSubsetVal = 0;
                        for (int j = 1; j < bigboard->getSpaceCount(); j++) {
                            Monopoly::Property *setProp;
                            setProp = dynamic_cast<Property *>(bigboard->getboard()[j].get());
                            if (setProp != NULL ){
                                if (setProp->getSetID() == i) {
                                    subsetVal++;
                                }
                            }
                        }
                        for (int k = 0; k < (short) players[highestBidder]->getUser_properties().size(); k++) {
                            if (players[highestBidder]->getUser_properties()[k].getSetID() == i) {
                                ownerSubsetVal++;
                            }
                        }
                        if (ownerSubsetVal == subsetVal) {
                            for (int j = 1; j < bigboard->getSpaceCount(); j++) {
                                Monopoly::Property *setProp;
                                setProp = dynamic_cast<Property *>(bigboard->getboard()[j].get());
                                if (setProp != NULL ){
                                    if (setProp->getSetID() == i) {
                                        setProp->setPropertySet(true);
                                    }
                                }
                            }
                            for (int k = 0;
                                 k < (short) players[highestBidder]->getUser_properties().size(); k++) {
                                if (players[highestBidder]->getUser_properties()[k].getSetID() == i) {
                                    players[highestBidder]->getUser_properties()[k].setPropertySet(true);
                                }
                            }
                            players[highestBidder]->getPropSetOwner()[i] = 1;
                            players[highestBidder]->getSubsetAmt()[i] = subsetVal;
                            players[highestBidder]->setSetOwner(true);
                        }
                    }
                    if (roll->isDoubles() &&
                        players[player_turn]->getRollCount() < rules->getMaxDoublesReRolls()) {
                        players[player_turn]->setRollCount(
                                players[player_turn]->getRollCount() + 1);
                        break;
                    } else {
                        setEnds_turn(true);
                        players[player_turn]->setRollCount(0);
                        break;
                    }
                }


                if (roll->isDoubles() &&
                    players[player_turn]->getRollCount() <
                    rules->getMaxDoublesReRolls()) {
                    players[player_turn]->setRollCount(
                            players[player_turn]->getRollCount() + 1);
                    break;
                } else {
                    setEnds_turn(true);
                    players[player_turn]->setRollCount(0);
                    break;
                }


            case 2:


                if (players[player_turn]->isSetOwner() &&
                    !players[player_turn]->isPropertyMaxed()) {
                    std::cout << "Which property do you want to upgrade?" << std::endl;

                    // display available upgrades//

                    subsetVal = 0;
                    maxprop = 0;
                    std::vector<int> availableUpgrades;

                    if (rules->isBuild_houses_evenly()) {

                        for (int i = 0; i <= bigboard->getMaxSetID(); i++) {
                            increment = 0;
                            for (int k = 0; k < (unsigned short) players[player_turn]->getUser_properties().size(); k++) {
                                if (players[player_turn]->getUser_properties()[k].getSetID() == i &&
                                    players[player_turn]->getPropSetOwner()[i] == 1) {
                                    if (increment == 0 &&
                                        (players[player_turn]->getUser_properties()[k].getHouses() > 0 ||
                                         players[player_turn]->getUser_properties()[k].getHotels() > 0)) {
                                        maxprop =
                                                players[player_turn]->getUser_properties()[k].getHouses() +
                                                players[player_turn]->getUser_properties()[k].getHotels() *
                                                rules->getHouses_before_hotels();
                                        increment++;
                                        players[player_turn]->getUser_properties()[k].setMostUpgrades(true);
                                    } else if (increment > 0 && maxprop >
                                                                players[player_turn]->getUser_properties()[k].getHouses() +
                                                                players[player_turn]->getUser_properties()[k].getHotels() *
                                                                rules->getHouses_before_hotels()) {
                                        maxprop =
                                                players[player_turn]->getUser_properties()[k].getHouses() +
                                                players[player_turn]->getUser_properties()[k].getHotels() *
                                                rules->getHouses_before_hotels();
                                        players[player_turn]->getUser_properties()[k].setMostUpgrades(true);
                                        players[player_turn]->getUser_properties()[k - 1].setMostUpgrades(
                                                false);
                                        increment--;
                                    } else if (increment > 0 && maxprop ==
                                                                players[player_turn]->getUser_properties()[k].getHouses() +
                                                                players[player_turn]->getUser_properties()[k].getHotels() *
                                                                rules->getHouses_before_hotels()) {
                                        players[player_turn]->getUser_properties()[k].setMostUpgrades(true);
                                        increment++;
                                    }
                                }

                            }
                            for (int l = 0; l < (unsigned short) players[player_turn]->getUser_properties().size(); l++) {
                                if (players[player_turn]->getUser_properties()[l].getSetID() == i &&
                                    players[player_turn]->getUser_properties()[i].getHotels() == 0) {
                                    if (increment == players[player_turn]->getSubsetAmt()[i] ||
                                        increment == 0) {
                                        std::cout << subsetVal << ". "
                                                  << players[player_turn]->getUser_properties()[l].getSpaceName()
                                                  << " [$";
                                        if (players[player_turn]->getUser_properties()[l].getHouses() <
                                            rules->getHouses_before_hotels()) {
                                            std::cout
                                                    << players[player_turn]->getUser_properties()[l].getHouseCost()
                                                    << "]" << std::endl;
                                        } else if (
                                                players[player_turn]->getUser_properties()[l].getHouses() <
                                                rules->getHouses_before_hotels()) {
                                            std::cout
                                                    << players[player_turn]->getUser_properties()[l].getHotelCost()
                                                    << "]" << std::endl;
                                        }
                                        availableUpgrades.push_back(
                                                players[player_turn]->getUser_properties()[l].getSpaceNum());
                                        subsetVal++;
                                    } else {
                                        if (!players[player_turn]->getUser_properties()[l].isMostUpgrades()) {
                                            std::cout << subsetVal << ". "
                                                      << players[player_turn]->getUser_properties()[l].getSpaceName()
                                                      << " [$";
                                            if (players[player_turn]->getUser_properties()[l].getHouses() <
                                                rules->getHouses_before_hotels()) {
                                                std::cout
                                                        << players[player_turn]->getUser_properties()[l].getHouseCost()
                                                        << "]" << std::endl;
                                            } else if (
                                                    players[player_turn]->getUser_properties()[l].getHouses() <
                                                    rules->getHouses_before_hotels()) {
                                                std::cout
                                                        << players[player_turn]->getUser_properties()[l].getHotelCost()
                                                        << "]" << std::endl;
                                            }
                                            availableUpgrades.push_back(
                                                    players[player_turn]->getUser_properties()[l].getSpaceNum());
                                            subsetVal++;
                                        }
                                    }
                                }
                            }
                        }
                        std::cout << "Your choice: ";
                        std::cin >> upgradeChoice;

                        for (int p = 0; p < (unsigned short) players[player_turn]->getUser_properties().size(); p++) {
                            if (players[player_turn]->getUser_properties()[p].getSpaceNum() ==
                                availableUpgrades[upgradeChoice]) {
                                if (players[player_turn]->getUser_properties()[p].getHouses() <
                                    rules->getHouses_before_hotels() &&
                                    players[player_turn]->getCash() >
                                    players[player_turn]->getUser_properties()[p].getHouseCost()) {
                                    players[player_turn]->getUser_properties()[p].setHouses(
                                            players[player_turn]->getUser_properties()[p].getHouses() + 1);
                                    players[player_turn]->setCash(
                                            players[player_turn]->getCash() -
                                            players[player_turn]->getUser_properties()[p].getHouseCost());
                                    Monopoly::Property *prop;
                                    prop = dynamic_cast<Property *> (bigboard->getboard()[p].get());
                                    prop->setHouses(
                                            players[player_turn]->getUser_properties()[p].getHouses() + 1);
                                    //bigboard->getboard()[p] = prop;
                                } else if (players[player_turn]->getUser_properties()[p].getHouses() <
                                           rules->getHouses_before_hotels() &&
                                           players[player_turn]->getCash() >
                                           players[player_turn]->getUser_properties()[p].getHotelCost()) {
                                    players[player_turn]->getUser_properties()[p].setHouses(0);
                                    players[player_turn]->getUser_properties()[p].setHotels(1);
                                    players[player_turn]->setCash(
                                            players[player_turn]->getCash() -
                                            players[player_turn]->getUser_properties()[p].getHotelCost());
                                    Monopoly::Property *prop;
                                    prop = dynamic_cast<Property *> (bigboard->getboard()[p].get());
                                    prop->setHouses(0);
                                    prop->setHotels(1);
                                    //bigboard->getboard()[p] = prop;
                                } else {
                                    std::cout << "You dont have enough money to purchase a house on this property"
                                              << std::endl;
                                }
                            }
                        }

                        increment = 0;
                        subsetVal = 0;
                        for (int i = 0; i < bigboard->getMaxSetID(); i++) {
                            if (players[player_turn]->getPropSetOwner()[i] == 1) {
                                for (int j = 0;
                                     j < (short) players[player_turn]->getUser_properties().size(); j++) {
                                    if (players[player_turn]->getUser_properties()[j].getSetID() == i &&
                                        players[player_turn]->getUser_properties()[j].getHotels() == 0) {
                                        increment++;
                                    }
                                }
                            }
                        }
                        if (increment == subsetVal) {
                            players[player_turn]->setPropertyMaxed(true);
                        }
                        availableUpgrades.clear();
                        break;
                    } else {
                        subsetVal = 0;
                        for (int i = 0; i <= bigboard->getMaxSetID(); i++) {
                            if (players[player_turn]->getPropSetOwner()[i] == 1) {
                                for (int j = 1;
                                     j < (short) players[player_turn]->getUser_properties().size(); j++) {
                                    if (players[player_turn]->getUser_properties()[j].getSetID() == i &&
                                        players[player_turn]->getUser_properties()[j].getHotels() == 0) {
                                        std::cout << subsetVal << ". "
                                                  << players[player_turn]->getUser_properties()[j].getSpaceName()
                                                  << " [$";
                                        if (players[player_turn]->getUser_properties()[j].getHouses() <
                                            rules->getHouses_before_hotels()) {
                                            std::cout
                                                    << players[player_turn]->getUser_properties()[j].getHouseCost()
                                                    << "]" << std::endl;
                                        } else if (
                                                players[player_turn]->getUser_properties()[j].getHouses() <
                                                rules->getHouses_before_hotels()) {
                                            std::cout
                                                    << players[player_turn]->getUser_properties()[j].getHotelCost()
                                                    << "]" << std::endl;
                                        }
                                        availableUpgrades.push_back(
                                                players[player_turn]->getUser_properties()[j].getSpaceNum());
                                        subsetVal++;
                                    }
                                }
                            }
                        }


                        std::cout << "Your choice: ";
                        std::cin >> upgradeChoice;

                        for (int p = 0; p < (short) players[player_turn]->getUser_properties().size(); p++) {
                            if (players[player_turn]->getUser_properties()[p].getSpaceNum() ==
                                availableUpgrades[upgradeChoice]) {
                                if (players[player_turn]->getUser_properties()[p].getHouses() <
                                    rules->getHouses_before_hotels() &&
                                    players[player_turn]->getCash() >
                                    players[player_turn]->getUser_properties()[p].getHouseCost()) {
                                    players[player_turn]->getUser_properties()[p].setHouses(
                                            players[player_turn]->getUser_properties()[p].getHouses() + 1);
                                    players[player_turn]->setCash(
                                            players[player_turn]->getCash() -
                                            players[player_turn]->getUser_properties()[p].getHouseCost());
                                    Monopoly::Property *prop;
                                    prop = dynamic_cast<Property *> (bigboard->getboard()[p].get());
                                    prop->setHouses(
                                            players[player_turn]->getUser_properties()[p].getHouses() + 1);
                                    //bigboard->getboard()[p] = prop;
                                } else if (players[player_turn]->getUser_properties()[p].getHouses() <
                                           rules->getHouses_before_hotels() &&
                                           players[player_turn]->getCash() >
                                           players[player_turn]->getUser_properties()[p].getHotelCost()) {
                                    players[player_turn]->getUser_properties()[p].setHouses(0);
                                    players[player_turn]->getUser_properties()[p].setHotels(1);
                                    players[player_turn]->setCash(
                                            players[player_turn]->getCash() -
                                            players[player_turn]->getUser_properties()[p].getHotelCost());
                                    Monopoly::Property *prop;
                                    prop = dynamic_cast<Property *> (bigboard->getboard()[p].get());
                                    prop->setHouses(0);
                                    prop->setHotels(1);
                                    //bigboard->getboard()[p] = prop;
                                } else {
                                    std::cout << "You dont have enough money to purchase a house on this property"
                                              << std::endl;
                                }
                            }
                        }
                        increment = 0;
                        subsetVal = 0;
                        for (int i = 0; i < bigboard->getMaxSetID(); i++) {
                            if (players[player_turn]->getPropSetOwner()[i] == 1) {
                                for (int j = 0;
                                     j < (unsigned short) players[player_turn]->getUser_properties().size(); j++) {
                                    if (players[player_turn]->getUser_properties()[j].getSetID() == i &&
                                        players[player_turn]->getUser_properties()[j].getHotels() == 0) {
                                        increment++;
                                    }
                                }
                            }
                        }
                        if (increment == subsetVal) {
                            players[player_turn]->setPropertyMaxed(true);
                        }
                        availableUpgrades.clear();
                        break;
                    }
                }
                else {
                    std::cout << "You don't have any properties that you can upgrade" << std::endl;
                }

                break;

            case 3:

                if (players[player_turn]->isUpgradeOwner()) {
                    std::cout << "You must downgrade properties in order to not go bankrupt" << std::endl;
                    std::cout << "Which property do you want to downgrade?" << std::endl;
                    for (int i = 0; i < (short) players[player_turn]->getUser_properties().size(); i++) {
                        if (players[player_turn]->getUser_properties()[i].isHasUpgrades()) {
                            std::cout << subsetVal << ". "
                                      << players[player_turn]->getUser_properties()[i].getSpaceName()
                                      << " [$";
                            if (players[player_turn]->getUser_properties()[i].getHouses() > 0) {
                                std::cout
                                        <<
                                        players[player_turn]->getUser_properties()[i].getHouseCost() /
                                        2
                                        << "]" << std::endl;
                            } else {
                                std::cout
                                        <<
                                        players[player_turn]->getUser_properties()[i].getHotelCost() /
                                        2
                                        << "]" << std::endl;
                            }
                            subsetVal++;
                        }
                    }

                    std::cout << "Your choice: ";
                    std::cin >> downGradeChoice;
                    increment = 0;
                    for (int i = 0; i < (unsigned short) players[player_turn]->getUser_properties().size(); i++) {
                        if (players[player_turn]->getUser_properties()[i].isHasUpgrades()) {
                            if (downGradeChoice == increment &&
                                players[player_turn]->getUser_properties()[i].getHouses() > 0) {
                                players[player_turn]->setCash(
                                        players[player_turn]->getCash() +
                                        players[player_turn]->getUser_properties()[i].getHouseCost() /
                                        2);
                                players[player_turn]->getUser_properties()[i].setHouses(
                                        players[player_turn]->getUser_properties()[i].getHouses() -
                                        1);
                            } else if (downGradeChoice == increment &&
                                       players[player_turn]->getUser_properties()[i].getHotels() >
                                       0) {
                                players[player_turn]->setCash(
                                        players[player_turn]->getCash() +
                                        players[player_turn]->getUser_properties()[i].getHotelCost() /
                                        2);
                                players[player_turn]->getUser_properties()[i].setHotels(
                                        players[player_turn]->getUser_properties()[i].getHotels() -
                                        1);
                                players[player_turn]->getUser_properties()[i].setHouses(
                                        players[player_turn]->getHousesb4hotels());
                            }
                            if (downGradeChoice == increment &&
                                players[player_turn]->getUser_properties()[i].getHouses() == 0) {
                                players[player_turn]->getUser_properties()[i].setHasUpgrades(false);
                            }
                            increment++;
                        }
                    }
                    subsetVal = 0;
                    for (int l = 0; l < (unsigned short) players[player_turn]->getUser_properties().size(); l++) {
                        if (players[player_turn]->getUser_properties()[l].isHasUpgrades()) {
                            subsetVal++;
                        }
                    }
                    if (subsetVal == 0) {
                        players[player_turn]->setUpgradeOwner(false);
                    }
                }
                else{
                    std::cout<< "You don't have any upgrades that you can sell" << std::endl;
                }
                break;


            case 4:
                players[player_turn]->setCash(0);

                for (int l = 0; l < bigboard->getSpaceCount(); l++) {
                    for (uint i = 0; i < (unsigned short) players[player_turn]->getUser_properties().size(); i++) {
                        if (bigboard->getboard()[l]->getSpaceNum() ==
                            players[player_turn]->getUser_properties()[i].getSpaceNum()) {
                            Monopoly::Property *tempProp;
                            tempProp = dynamic_cast<Property *>(bigboard->getboard()[l].get());
                            //dynamic_cast<Property*>(bigboard->getboard()[j])->setOwner(players[player_turn]->getPlayerToPay());
                            tempProp->setOwner(-1);
                            tempProp->setHouses(0);
                            tempProp->setHotels(0);
                            //bigboard->getboard()[i] = tempProp;
                        }

                    }
                }
                players[player_turn]->setPlayer_num(-1);
                players[player_turn]->getUser_properties().clear();
                setEnds_turn(true);
                break;
        }
    }
}





// getters and setters //

int Monopoly::Gamestate::getPlayers_amt() const {
    return players_amt;
}

void Monopoly::Gamestate::setPlayers_amt(int players_amt) {
    Gamestate::players_amt = players_amt;
}

int Monopoly::Gamestate::getPlayer_turn() const {
    return player_turn;
}

void Monopoly::Gamestate::setPlayer_turn(int player_turn) {
    Gamestate::player_turn = player_turn;
}

bool Monopoly::Gamestate::isEnds_turn() const {
    return ends_turn;
}

void Monopoly::Gamestate::setEnds_turn(bool ends_turn) {
    Gamestate::ends_turn = ends_turn;
}

int Monopoly::Gamestate::getChoice() const {
    return choice;
}

void Monopoly::Gamestate::setChoice(int choice) {
    Gamestate::choice = choice;
}

int Monopoly::Gamestate::getTurnCount() const {
    return turnCount;
}

void Monopoly::Gamestate::setTurnCount(int turnCount) {
    Gamestate::turnCount = turnCount;
}
