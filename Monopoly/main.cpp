#include <iostream>
#include "Gamestate.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;


Gamestate setup(char* Rules, char* Board, char* RandomNums);
bool is_game_over(Gamestate *gamestate);
void display_game_state(Gamestate *gamestate);
Move get_move(Player *player);
void make_move(Move *move, Gamestate *gamestate);
void change_turn(Gamestate *gamestate);
void declare_winners(Gamestate *gamestate);
int dice_roll(Gamestate *gamestate);


void delete_game_state(Gamestate *gamestate){
    gamestate->random->close();
    delete gamestate->random;
    free(gamestate->properties);
    free(gamestate->players);

};


int main(int argc, char** argv) {

    Gamestate game_state = setup(argv[1], argv[2], argv[3]);
    Move move;

    while(!is_game_over(&game_state)){
        do{
            display_game_state(&game_state);
            move = get_move(&game_state.players[game_state.player_turn]);
            make_move(&move, &game_state);
        }while(!move.ends_turn);
        change_turn(&game_state);
    }

    display_game_state(&game_state);
    declare_winners(&game_state);
    delete_game_state(&game_state);
    return 0;
}

Gamestate setup(char* Rules, char* Board, char* RandomFile){

    Gamestate game_state;
   //  game_state  = (Gamestate*)malloc(sizeof (Gamestate));
   //  game_state = new Gamestate;



    ifstream file(Rules);
    string buffer = "";


    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream coneyo(buffer);
    coneyo >> game_state.starting_cash;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream cone2(buffer);
    cone2 >> game_state.turn_limit;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream cone3(buffer);
    cone3 >> game_state.player_endgame;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream cone4(buffer);
    cone4 >> game_state.property_set_multiplier;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream cone5(buffer);
    cone5 >> game_state.houses_before_hotels;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    game_state.build_houses_evenly = buffer == "Yes" ? true : false;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    game_state.freeparking = buffer == "Yes" ? true : false;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    game_state.auction = buffer == "Yes" ? true : false;

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream cone6(buffer);
    cone6 >> game_state.go_multiplier;



    ifstream file2(Board);
    string buffer2 = "";

    int i = 1;

    while (getline(file2,buffer2)){

        i = i +1;

    }


    file2.clear();
    file2.seekg(0, ios::beg);

    const int BOARD_SPACES = i - 5;

    game_state.spaceCount = BOARD_SPACES;





    for (i = 0 ; i < 4; ++i){
        getline(file2,buffer2);
    }




 //   game_state->properties[BOARD_SPACES];
    game_state.properties= (board_space*)malloc(BOARD_SPACES * sizeof(board_space));
    // game_state.properties = new board_space;


    const int COLUMNS = 10;
    getline(file2,buffer2,',');
    game_state.properties[0].type = buffer2;
    getline(file2,buffer2,',');
    game_state.properties[0].price =stoi(buffer2);
    getline(file2,buffer2,',');
    game_state.properties[0].name = buffer2;
    game_state.properties[0].owner = -2;
    game_state.properties[0].spaceNum = 0;
    for (int k =0; k<6; k++){
        getline(file2,buffer2,',');
    }

    // the below for loop starts at line 6, which is where the go space starts
    for (i =1; i< BOARD_SPACES; i++){
        // insert struct for board space, parse out individual values for each part of struct to each space
        // make sure this is dynamically allocated with respect to the changing amount of board spaces




        for (int j=0; j< COLUMNS-1; j++){


                getline(file2,buffer2, ',');

                switch (j) {
                    case 0:
                        game_state.properties[i].type = buffer2;
                        break;

                    case 1:

                        game_state.properties[i].setID = stoi(buffer2);
                        break;

                    case 2:
                        game_state.properties[i].subsetID = stoi(buffer2);
                        break;
                    case 3:
                        game_state.properties[i].name = buffer2;
                        break;

                    case 4:
                        game_state.properties[i].price = stoi(buffer2);
                        break;
                    case 5:
                        game_state.properties[i].house_cost = stoi(buffer2);
                        break;
                    case 6:
                        game_state.properties[i].hotel_cost = stoi(buffer2);
                        break;
                    case 7:
                        game_state.properties[i].rent = stoi(buffer2);
                        break;
                    case 8:
                        game_state.properties[i].rent_with_house = stoi(buffer2);
                        break;
                    case 9:
                        game_state.properties[i].rent_with_hotel = stoi(buffer2);
                        break;



                }

            game_state.properties[i].owner = -1;
            game_state.properties[i].houses = 0;
            game_state.properties[i].hotels = 0;
            game_state.properties[i].spaceNum = i;

        }





    }


    game_state.maxSetID = game_state.properties[game_state.spaceCount-1].setID;


    ifstream *file3= new ifstream(RandomFile);
    game_state.random = file3;







    cout<< "How many players will be playing: ";
    cin >> game_state.players_amt;



 //   game_state.players[game_state.players_amt];
    game_state.players = (Player*)malloc(game_state.players_amt*sizeof(Player));


    for (i=0; i<game_state.players_amt; i++){
        game_state.players[i].cash = game_state.starting_cash;
        game_state.players[i].position = 0;
        game_state.players[i].user_properties = vector <board_space>();
        game_state.players[i].player_num = i;
        game_state.players[i].roll= false;

    }

    game_state.turncount = 0;
    game_state.player_turn = 0;


    file.close();
    file2.close();

    return game_state;

}




bool is_game_over(Gamestate *gamestate) {
    bool game_over = false;

    if (gamestate->turncount>= gamestate->turn_limit && gamestate->turn_limit!=-1){
        game_over = true;
    }

    int players_remaining = 0;
    for (int i = 0; i< gamestate->players_amt; i++){
        if (gamestate->players[i].player_num != -1) {
            players_remaining = players_remaining + 1;
        }

    }
    if (players_remaining <= gamestate->player_endgame){
        game_over = true;
    }


    return game_over;

// returns false while certain parameters are met depending on input from rule file
// ie turn limit, number of players left to end game,
// bankruptcy function that autokicks player and forfeits properties
}


void display_game_state(Gamestate *game_state){



    for (int l = 0; l< game_state->spaceCount; l++){
        cout << l << " |  " << game_state->properties[l].name << "\t|\t";
        for (int k = 0 ; k< game_state->players_amt; k++){
            if (game_state->players[k].position == l && game_state->players[k].player_num != -1){
                cout << game_state->players[k].player_num;
            }
        }
        cout << endl;
    }




}


Move get_move(Player *player){
    Move output;
    output.ends_turn = false;
    cout<< "Player " << player->player_num << " please choose an action" <<  endl;
    if (player->roll == false){
        cout << "1: Roll Dice" << endl;
        cout << "2: Inspect Player" << endl;
        cout << "3: Leave Game" << endl;
    }
    else{
        cout << "1: End turn" << endl;
        cout << "2: Inspect Player" << endl;
        cout << "3: Leave Game" << endl;
    }

    cin >> output.choice;

    return output;
}


void make_move(Move *move, Gamestate *gamestate){

     if (move->ends_turn != true) {

        if (gamestate->players[gamestate->player_turn].roll == false) {
            int move_num = 0;
            int prev_subset = 0;
            string properties_owned = "";
            int temp_pos = 0;
            int temp_subset =0;
            switch (move->choice) {
                case 1:
                    move_num = dice_roll(gamestate);
                    gamestate->players[gamestate->player_turn].roll = true;

                    temp_pos = gamestate->players[gamestate->player_turn].position + move_num;

                    if (temp_pos >= gamestate->spaceCount) {
                        // this if statements and its nested branches represent passing or landing on go
                        while (temp_pos > gamestate->spaceCount -1) {
                            temp_pos -= gamestate->spaceCount;
                            gamestate->players[gamestate->player_turn].cash += (gamestate->properties[0].price);
                        }
                        gamestate->players[gamestate->player_turn].position = temp_pos;
                        if (gamestate->players[gamestate->player_turn].position == 0) {
                            gamestate->players[gamestate->player_turn].cash += (gamestate->go_multiplier *
                                                                                gamestate->properties[0].price);
                        }
                    }
                    else {
                        gamestate->players[gamestate->player_turn].position = temp_pos;
                    }
                    // property purchase branch
                    if (gamestate->properties[gamestate->players[gamestate->player_turn].position].owner
                        == -1 && gamestate->players[gamestate->player_turn].cash >=
                                 gamestate->properties[gamestate->players[gamestate->player_turn].position].price ) {
                        cout << gamestate->properties[gamestate->players[gamestate->player_turn].position].name << " is "
                             << gamestate->properties[gamestate->players[gamestate->player_turn].position].price << endl;
                        cout << "Would you like to buy it?  y / n" << endl;

                        char buy;
                        cin >> buy;

                        if (buy == 'y') {

                            gamestate->properties[gamestate->players[gamestate->player_turn].position].owner =
                                    gamestate->players[gamestate->player_turn].player_num;
                            gamestate->players[gamestate->player_turn].user_properties.push_back(
                                    gamestate->properties[gamestate->players[gamestate->player_turn].position]);
                            gamestate->players[gamestate->player_turn].cash -= gamestate->properties[gamestate->players[gamestate->player_turn].position].price;
                        }

                        else {
                            /// auction later //
                        }
                    }
                        // someone else owns the property (use for loops to check set ownership for set mulitplier application //
                    else if (gamestate->properties[gamestate->players[gamestate->player_turn].position].owner != gamestate->players[gamestate->player_turn].player_num &&
                            gamestate->properties[gamestate->players[gamestate->player_turn].position].owner != -1){
                        int subsetprop = 0;
                        for (int i = 1; i < gamestate->spaceCount; i++) {
                            if (gamestate->properties[gamestate->players[gamestate->player_turn].position].setID == gamestate->properties[i].setID){
                                subsetprop++;
                            }
                        }
                        int owns_subset = 0;
                        for (int i = 1; i < gamestate->spaceCount; i++) {
                            if ((gamestate->properties[gamestate->players[gamestate->player_turn].position].setID == gamestate->properties[i].setID)&&
                                    gamestate->properties[i].owner == gamestate->properties[gamestate->players[gamestate->player_turn].position].owner){
                                owns_subset++;
                            }
                        }
                        if (owns_subset == subsetprop){
                            if (gamestate->players[gamestate->player_turn].cash >= gamestate->properties[gamestate->players[gamestate->player_turn].position].rent *
                                                                                   gamestate->property_set_multiplier) {
                                gamestate->players[gamestate->player_turn].cash -= (
                                        gamestate->properties[gamestate->players[gamestate->player_turn].position].rent *
                                        gamestate->property_set_multiplier);
                                gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].cash += (
                                        gamestate->properties[gamestate->players[gamestate->player_turn].position].rent *
                                        gamestate->property_set_multiplier);
                            }
                                // bankruptcy loop //
                            else{
                                cout << "Player" << gamestate->players[gamestate->player_turn].player_num<<" has gone bankrupt." << endl;

                                gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].cash +=
                                        gamestate->players[gamestate->player_turn].cash;
                                gamestate->players[gamestate->player_turn].cash = 0;
                                gamestate->players[gamestate->player_turn].player_num = -1;
                                for (uint i=0; i< gamestate->players[gamestate->player_turn].user_properties.size(); i++){
                                    gamestate->players[gamestate->player_turn].user_properties[i].owner=
                                            gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].player_num;
                                    gamestate->properties[gamestate->players[gamestate->player_turn].user_properties[i].spaceNum].owner =
                                            gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].player_num;
                                    gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].user_properties.push_back(
                                            gamestate->players[gamestate->player_turn].user_properties[i]);

                                }
                                gamestate->players[gamestate->player_turn].user_properties.clear();

                                move->ends_turn = true;
                            }
                        }
                        else{
                            if (gamestate->players[gamestate->player_turn].cash >= gamestate->properties[gamestate->players[gamestate->player_turn].position].rent) {
                                gamestate->players[gamestate->player_turn].cash -= gamestate->properties[gamestate->players[gamestate->player_turn].position].rent;
                                gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].cash +=
                                        gamestate->properties[gamestate->players[gamestate->player_turn].position].rent;
                            }
                            else{
                                cout << "Player" << gamestate->players[gamestate->player_turn].player_num<<" has gone bankrupt." << endl;

                                gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].cash +=
                                        gamestate->players[gamestate->player_turn].cash;
                                gamestate->players[gamestate->player_turn].cash = 0;
                                gamestate->players[gamestate->player_turn].player_num = -1;
                                for (uint i=0; i< gamestate->players[gamestate->player_turn].user_properties.size(); i++){
                                    gamestate->players[gamestate->player_turn].user_properties[i].owner=
                                            gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].player_num;
                                    gamestate->properties[gamestate->players[gamestate->player_turn].user_properties[i].spaceNum].owner =
                                            gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].player_num;
                                    gamestate->players[gamestate->properties[gamestate->players[gamestate->player_turn].position].owner].user_properties.push_back(
                                            gamestate->players[gamestate->player_turn].user_properties[i]);
                                }
                                gamestate->players[gamestate->player_turn].user_properties.clear();

                                move->ends_turn = true;
                            }
                        }
                    }

                            break;
                case 2:
                    cout <<  "Which player would you like to inspect?\n";
                    // do a for loop to list all players available to be inspected //
                    int player_inspect;
                    cin >> player_inspect;
                    cout << "Player " << gamestate->players[player_inspect].player_num << endl;
                    cout << "  Cash: $"  << gamestate->players[player_inspect].cash << endl;
                    cout << "  Properties Owned\n";

                    prev_subset = -1;

                    for (int i = 1; i<gamestate->spaceCount; i++) {
                            if (prev_subset < gamestate->properties[i].setID){
                                properties_owned.append("\n");
                                properties_owned.append(to_string(gamestate->properties[i].setID));
                                properties_owned.append(" | ");
                                prev_subset++;
                                temp_subset = 0;
                            }
                            if (gamestate->properties[i].owner == gamestate->players[player_inspect].player_num) {
                                if (temp_subset > 1) {
                                    properties_owned.append(" | ");
                                }
                                properties_owned.append(gamestate->properties[i].name);
                                temp_subset++;
                            }

                        }
                            cout << properties_owned << "\n" << endl;
                    break;
                case 3:
                    cout << "Player" << gamestate->players[gamestate->player_turn].player_num << " has left the game." << endl;
                    gamestate->players[gamestate->player_turn].cash = 0;
                    gamestate->players[gamestate->player_turn].player_num = -1;
                    for (uint i=0; i< gamestate->players[gamestate->player_turn].user_properties.size(); i++){
                        gamestate->players[gamestate->player_turn].user_properties[i].owner= -1;
                    }
                    gamestate->players[gamestate->player_turn].user_properties.clear();

                    move->ends_turn = true;

                    break;
            }
        }
        else{
            gamestate->players[gamestate->player_turn].roll = false;
            int prev_subset = 0;
            string properties_owned = "";
            switch (move->choice) {

                case 1:
                    move->ends_turn = true;
                    break;
                case 2:
                    cout <<  "Which player would you like to inspect?\n";
                    // do a for loop to list all players available to be inspected //
                    int player_inspect;
                    cin >> player_inspect;
                    cout << "Player " << gamestate->players[player_inspect].player_num << endl;
                    cout << "  Cash: $"  << gamestate->players[player_inspect].cash << endl;
                    cout << "  Properties Owned\n";

                    prev_subset = -1;
                    for (int i = 1; i<gamestate->spaceCount; i++) {
                        if (prev_subset < gamestate->properties[i].setID){
                            properties_owned.append("\n");
                            properties_owned.append(to_string(gamestate->properties[i].setID));
                            properties_owned.append(" | ");
                            prev_subset++;
                        }
                        if (gamestate->properties[i].owner == gamestate->players[player_inspect].player_num) {
                            properties_owned.append(gamestate->properties[i].name);

                        }
                    }
                    cout<< properties_owned << "\n" << endl;
                    gamestate->players[gamestate->player_turn].roll = true;
                    break;
                case 3:
                    cout << "Player" << gamestate->players[gamestate->player_turn].player_num << " has left the game." << endl;
                    gamestate->players[gamestate->player_turn].cash = 0;
                    gamestate->players[gamestate->player_turn].player_num = -1;
                    for (uint i=0; i< gamestate->players[gamestate->player_turn].user_properties.size(); i++){
                        gamestate->players[gamestate->player_turn].user_properties[i].owner= -1;
                    }
                    gamestate->players[gamestate->player_turn].user_properties.clear();

                    move->ends_turn = true;
                    break;
            }
        }
     }

 }


void change_turn(Gamestate *gamestate) {

    for (int i=0; i<gamestate->players_amt; i++){

    if (gamestate->player_turn <= gamestate->players_amt - 2 &&
        (gamestate->players[gamestate->player_turn + 1].player_num != -1)) {
        gamestate->player_turn++;
        break;
    } else if (gamestate->player_turn == gamestate->players_amt - 1 && gamestate->players[0].player_num != -1) {
        gamestate->player_turn = 0;
        break;
    }
        else{
        gamestate->player_turn++;
    }
}

}


void declare_winners(Gamestate *game_state){
    vector<int> finalWinners;
    int maxPrice = 0;

    int playerwinners[game_state->players_amt];



    for (int i = 0; i < game_state->players_amt; i++){
        if (game_state->players[i].player_num != -1) {
            playerwinners[i] = game_state->players[i].cash;
            for (uint j = 0; j < game_state->players[i].user_properties.size(); j++) {
                playerwinners[i] += game_state->players[i].user_properties[j].price;
            }
        }
        else{
            playerwinners[i] = 0;
        }
    }

    maxPrice = playerwinners[0];

    for (int m = 1; m< game_state->players_amt; ++m){
        if (playerwinners[m]> playerwinners[m-1]){
            maxPrice = playerwinners[m];
        }
    }


    for (int k = 0; k< game_state->players_amt; k++){
        if (playerwinners[k] == maxPrice){
            finalWinners.push_back(k);
        }
    }
    if (finalWinners.size()>1) {
        cout << "The winners are: " << endl;


        for (uint l = 0; l < finalWinners.size(); l++) {
            cout << "Player " << finalWinners[l] << endl;

        }
    }

    else{
        cout <<  "The winner is: "  << finalWinners[0] <<"is the winner." << endl;
    }

}



int dice_roll(Gamestate *gamestate){


    string buffer4;
    getline(*gamestate->random,buffer4);

    stringstream tempstring(buffer4);
    int temp_rand_var;
    tempstring >> temp_rand_var;
    temp_rand_var = temp_rand_var%5 + 1;
    getline(*gamestate->random,buffer4);

    stringstream tempstring1(buffer4);
    int temp_rand_var1;
    tempstring1 >> temp_rand_var1;
    temp_rand_var1 = temp_rand_var1%5 + 1;

    cout << "You rolled a " << temp_rand_var+temp_rand_var1 << "!" <<endl;
    return temp_rand_var + temp_rand_var1;
}