//
// Created by Adam Levin on 2/6/18.
//
#include "Gamestate.h"
#include "Move.h"

void make_move(Move *move, Gamestate *gamestate){

    if (!move->isEnds_turn()) {

        if (gamestate->getPlayers()[gamestate->getPlayer_turn()].isRoll() == false) {
            int move_num = 0;
            int prev_subset = 0;
            string properties_owned = "";  // come back
            int temp_pos = 0;
            int temp_subset = 0;
            int while_val = 0;
            switch (move->getChoice()) {
                case 1:
                    move_num = gamestate->dice_roll();
                    move_num = dice_roll(gamestate);
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].setRoll(true);

                    temp_pos = gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition() + move_num;

                    if (temp_pos >= gamestate->getSpaceCount()) {
                        // this if statements and its nested branches represent passing or landing on go
                        while (temp_pos > gamestate->getSpaceCount()-1) {
                            temp_pos -= gamestate->getSpaceCount();
                            while_val++;
                        }
                        if (while_val > 0 && temp_pos == 0){
                            gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash(gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() +
                                                                                                 (gamestate->getProperties()[0].getPrice())*(while_val-1));
                            gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash ( (gamestate->getProperties()[0].getPrice())*(gamestate->getGo_multiplier()));
                        }
                        else if(while_val > 0 && temp_pos != 0){
                            gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash(gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() +
                                                                                         (gamestate->getProperties()[0].getPrice())*(while_val));
                        }
                        gamestate->getPlayers()[gamestate->getPlayer_turn()].setPosition(temp_pos);
                        if (while_val == 0 && gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition() == 0) {
                            gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash ( (gamestate->getProperties()[0].getPrice())*(gamestate->getGo_multiplier()));
                        }
                    }
                    else {
                        gamestate->getPlayers()[gamestate->getPlayer_turn()].setPosition(temp_pos);
                    }
                    // property purchase branch

                    if (gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()
                        == -1 && gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() >=
                                 gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getPrice() ) {
                        //    cout << Gamestate->properties[gamestate->getPlayers()[gamestate->getPlayer_turn()].position].name << " is "
                        //         << Gamestate->properties[gamestate->getPlayers()[gamestate->getPlayer_turn()].position].price << endl;


                        cout << "Player " << gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() << " would you like to buy ";
                        cout << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getName()
                             << " for $" << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getPrice() << "?" << endl;     //Fixed 1/30/18
                        cout << "The rent on this property is $" << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent() << endl;
                        cout << "You currently have $" << gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() << endl;
                        cout << "Y for yes, N for no: " << endl;
                        char buy;
                        cin >> buy;


                        /*char buy;
                        cin >> buy;*/

                        if (buy == 'y') {

                            gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].setOwner(
                                    gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num());
                            gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties.push_back(
                                    gamestate->properties[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()]);     // need to fix!!! how to push back vector in getter and setter///
                            // also do we even need to create a vector of board spaces that each player owns? isnt setting the owner value enough? // does this concept also apply to the bankruptcy loop?
                            gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash ( gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() -
                                                                                                   gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getPrice());
                        }

                        else {
                            /// auction later //
                        }
                    }
                    else if (  gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()
                               == -1 && gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() <
                                        gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getPrice())  {

                        cout << "Player " << gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() << " you do not have enough money to purchase " << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getName() << endl;
                        cout << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getName() << " costs $"
                             << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getPrice() << ", but you only have $" << gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() << endl;

                    }


                        // someone else owns the property (use for loops to check set ownership for set mulitplier application //
                    else if (gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner() != gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() &&
                             gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner() != -1 && gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition() != 0){
                        int subsetprop = 0;
                        for (int i = 1; i < gamestate->getSpaceCount(); i++) {
                            if (gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getSetID() == gamestate->getProperties()[i].getSetID()){
                                subsetprop++;
                            }
                        }
                        int owns_subset = 0;
                        for (int i = 1; i < gamestate->getSpaceCount(); i++) {
                            if ((gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getSetID() == gamestate->getProperties()[i].getSetID())&&
                                gamestate->getProperties()[i].getOwner() == gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()){
                                owns_subset++;
                            }
                        }
                        if (owns_subset == subsetprop){
                            if (gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() >= gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent() *
                                                                                   gamestate->getProperty_set_multiplier()) {
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash (gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() -
                                        gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent() *
                                        gamestate->getProperty_set_multiplier());
                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].setCash(
                                        gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent() *
                                        gamestate->getProperty_set_multiplier()+
                                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].getCash());
                                cout << "Player " << gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() << " payed Player "
                                     << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()
                                     << "$" << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent()*gamestate->getProperty_set_multiplier() << " for landing on " <<
                                     gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getName() << endl;
                            }
                                // bankruptcy loop //
                            else{
                                cout << "Player " << gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() << " went bankrupt to Player " <<
                                     gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner() << endl;

                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].setCash (
                                        gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash()+
                                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].getCash())  ; // adds money to owner of prop
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash(0); // takes cash from broke player sets to 0
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].setPlayer_num (-1); // semantically removes player from game by setting to -1
                                for (uint i=0; i< gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties().size(); i++){
                                    gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties()[i].setOwner (
                                            gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].getPlayer_num());
                                    gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties[i].spaceNum].owner =
                                            gamestate->players[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].owner].player_num;
                                    gamestate->players[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].owner].user_properties.push_back(
                                            gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties[i]);

                                }
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties().clear();

                                move->setEnds_turn(true);
                            }
                        }
                        else{
                            if (gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() >= gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent()) {

                                gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash (gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash() -
                                                                                              gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent());
                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].setCash(
                                        gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent() +
                                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].getCash());
                                cout << "Player " << gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() << " payed Player "
                                     << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()
                                     << "$" << gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getRent() << " for landing on " <<
                                     gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getName() << endl;

                            }
                            else{
                                cout << "Player " << gamestate->getPlayers()[gamestate->getPlayer_turn()].getPlayer_num() << " went bankrupt to Player " <<
                                     gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner() << endl;

                                gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].setCash (
                                        gamestate->getPlayers()[gamestate->getPlayer_turn()].getCash()+
                                        gamestate->getPlayers()[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].getOwner()].getCash())  ; // adds money to owner of prop
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash(0); // takes cash from broke player sets to 0
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].setPlayer_num (-1); // semantically removes player from game by setting to -1
                                for (uint i=0; i< gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties().size(); i++){
                                    gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties[i].owner=
                                            gamestate->players[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].owner].player_num;
                                    gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties[i].spaceNum].owner =
                                            gamestate->players[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].owner].player_num;
                                    gamestate->players[gamestate->getProperties()[gamestate->getPlayers()[gamestate->getPlayer_turn()].getPosition()].owner].user_properties.push_back(
                                            gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties[i]);
                                }
                                gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties.clear();

                                move->setEnds_turn(true);
                            }
                        }
                    }

                    break;
                case 2:
                    cout <<  "Which player would you like to inspect?\n";
                    // do a for loop to list all players available to be inspected //
                    for (int i = 0; i < gamestate->getPlayers_amt(); i++){
                        if (gamestate->getPlayers()[i].getPlayer_num() != -1) {
                            cout << gamestate->getPlayers()[i].getPlayer_num() << " for Player " << gamestate->getPlayers()[i].getPlayer_num() << endl;
                        }
                    }
                    cout << "Your choice: ";
                    int player_inspect;
                    cin >> player_inspect;
                    cout << "Player " << gamestate->getPlayers()[player_inspect].getPlayer_num() << endl;
                    cout << "  Cash: $"  << gamestate->getPlayers()[player_inspect].getCash() << endl;
                    cout << "  Properties owned\n";

                    prev_subset = -1;
                    temp_subset = 0;
                    for (int i = 1; i<gamestate->getSpaceCount(); i++) {
                        if (prev_subset < gamestate->getProperties()[i].getSetID()){
                            properties_owned.append("\n");
                            properties_owned.append(to_string(gamestate->getProperties()[i].getSetID()));
                            properties_owned.append(" : ");
                            prev_subset++;
                            temp_subset = 0;
                        }


                        if ((gamestate->getProperties()[i].getOwner() == gamestate->getPlayers()[player_inspect].getPlayer_num())) {
                            temp_subset++;
                            if (temp_subset > 1){
                                properties_owned.append(" | ");
                            }
                            properties_owned.append(gamestate->getProperties()[i].getName());

                        }

                    }
                    cout << properties_owned << "\n" << endl;
                    break;
                case 3:
                    //cout << "Player" << gamestate->getPlayers()[gamestate->getPlayer_turn()].player_num << " has left the game." << endl;
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash(0);
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].setPlayer_num(-1);
                    for (uint i=0; i< gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties().size(); i++){
                        gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties()[i].setOwner(-1);
                    }
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties.clear();

                    move->setEnds_turn(true);

                    break;
            }
        }
        else{
            gamestate->getPlayers()[gamestate->getPlayer_turn()].roll = false;
            int prev_subset = 0;
            int temp_subset = 0;
            string properties_owned = "";
            switch (move->choice) {

                case 1:
                    move->ends_turn = true;
                    break;
                case 2:
                    cout <<  "Which player would you like to inspect?\n";
                    // do a for loop to list all players available to be inspected //
                    for (int i = 0; i < gamestate->getPlayers_amt(); i++){
                        if (gamestate->getPlayers()[i].getPlayer_num() != -1) {
                            cout << gamestate->getPlayers()[i].getPlayer_num() << " for Player " << gamestate->getPlayers()[i].getPlayer_num() << endl;
                        }
                    }
                    cout << "Your choice: ";
                    int player_inspect;
                    cin >> player_inspect;
                    cout << "Player " << gamestate->getPlayers()[player_inspect].getPlayer_num() << endl;
                    cout << "  Cash: $"  << gamestate->getPlayers()[player_inspect].getCash() << endl;
                    cout << "  Properties owned\n";

                    prev_subset = -1;
                    temp_subset = 0;
                    for (int i = 1; i<gamestate->getSpaceCount(); i++) {
                        if (prev_subset < gamestate->getProperties()[i].getSetID()){
                            properties_owned.append("\n");
                            properties_owned.append(to_string(gamestate->getProperties()[i].getSetID()));
                            properties_owned.append(" : ");
                            prev_subset++;
                            temp_subset = 0;
                        }


                        if ((gamestate->getProperties()[i].getOwner() == gamestate->getPlayers()[player_inspect].getPlayer_num())) {
                            temp_subset++;
                            if (temp_subset > 1){
                                properties_owned.append(" | ");
                            }
                            properties_owned.append(gamestate->getProperties()[i].getName());

                        }

                    }
                    cout << properties_owned << "\n" << endl;
                    break;
                case 3:
                    //cout << "Player" << gamestate->getPlayers()[gamestate->getPlayer_turn()].player_num << " has left the game." << endl;
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].setCash(0);
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].setPlayer_num(-1);
                    for (uint i=0; i< gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties().size(); i++){
                        gamestate->getPlayers()[gamestate->getPlayer_turn()].getUser_properties()[i].setOwner(-1);
                    }
                    gamestate->getPlayers()[gamestate->getPlayer_turn()].user_properties.clear();

                    move->setEnds_turn(true);

                    break;
            }
        }
    }

}

bool Move::isEnds_turn() const {
    return ends_turn;
}

void Move::setEnds_turn(bool ends_turn) {
    Move::ends_turn = ends_turn;
}

int Move::getChoice() const {
    return choice;
}

void Move::setChoice(int choice) {
    Move::choice = choice;
}
