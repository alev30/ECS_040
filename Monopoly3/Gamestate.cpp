//
// Created by Adam Levin on 2/6/18.
//

#include "Gamestate.h"





void Gamestate::setup(char* Rules, char* Board, char* RandomFile){






    ifstream file(Rules);
    string buffer = "";


    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setStarting_cash(stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setTurn_limit(stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setPlayer_endgame(stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);


    setProperty_set_multiplier(stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    setHouses_before_hotels(stoi(buffer));

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    if (buffer == "Yes"){
        setBuild_houses_evenly(true);
    }
    else{
        setBuild_houses_evenly(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);


    if (buffer == "Yes"){
       setFreeparking(true);
    }
    else{
        setFreeparking(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);

    if (buffer == "Yes"){
        setAuction(true);
    }
    else{
        setAuction(false);
    }

    getline(file,buffer,':');
    getline(file, buffer, ' ');
    getline(file, buffer);
    stringstream cone6(buffer);


    setGo_multiplier(stoi(buffer));



    ifstream file2(Board);
    string buffer2 = "";

    int i = 1;

    while (getline(file2,buffer2)){

        i = i +1;

    }


    file2.clear();
    file2.seekg(0, ios::beg);

    const int BOARD_SPACES = i - 5;

    setSpaceCount(BOARD_SPACES);





    for (i = 0 ; i < 4; ++i){
        getline(file2,buffer2);
    }




    //   game_state->properties[BOARD_SPACES];


    // game_state.properties= (board_space*)malloc(BOARD_SPACES * sizeof(board_space));
    // game_state.properties = new board_space;


    const int COLUMNS = 10;
    getline(file2,buffer2,',');
    getProperties()[0].setType(buffer2);
    getline(file2,buffer2,',');
    getProperties()[0].setPrice(stoi(buffer2));
    getline(file2,buffer2,',');
    getProperties()[0].setName(buffer2);
    getProperties()[0].setOwner(-2);
    getProperties()[0].setSpaceNum(0);
    for (int k =0; k<6; k++){
        getline(file2,buffer2,',');
    }

    // the below for loop starts at line 6, which is where the go space starts
    for (i =1; i< BOARD_SPACES; i++){
        // insert struct for board space, parse out individual values for each part of struct to each space
        // make sure this is dynamically allocated with respect to the changing amount of board spaces

        //std::string g = "G";
        //std::string h = "H";


        for (int j=0; j< COLUMNS-1; j++){


            getline(file2,buffer2, ',');

            switch (j) {
                case 0:
                    getProperties()[i].setType(buffer2);
                    break;

                case 1:

                    getProperties()[i].setSetID(stoi(buffer2));
                    break;

                case 2:
                    getProperties()[i].setSubsetID(stoi(buffer2));
                    break;
                case 3:
                    getProperties()[i].setName(buffer2);
                    /*if (getProperties()[i].name == g) {
                        getProperties()[i].setID += 1;
                    }
                    if (getProperties()[i].name == h) {
                        getProperties()[i].setID += 1;
                    }*/
                    break;

                case 4:
                    getProperties()[i].setPrice(stoi(buffer2));
                    break;
                case 5:
                    getProperties()[i].setHouse_cost(stoi(buffer2));
                    break;
                case 6:
                    getProperties()[i].setHotel_cost(stoi(buffer2));
                    break;
                case 7:
                    getProperties()[i].setRent(stoi(buffer2));
                    break;
                case 8:
                    getProperties()[i].setRent_with_house(stoi(buffer2));
                    break;
                case 9:
                    getProperties()[i].setRent_with_hotel(stoi(buffer2));
                    break;

            }

        }

        getProperties()[i].setOwner(-1);
        getProperties()[i].setHouses(0);
        getProperties()[i].setHotels(0);
        getProperties()[i].setSpaceNum(i);

    }








    setMaxSetID(getProperties()[getSpaceCount()-1].getSetID());


    ifstream *file3= new ifstream(RandomFile);
    setRandom(file3);





    int tempPlayeramt;

    cout << "How many players will be playing: ";
    cin >> tempPlayeramt;
    setPlayers_amt(tempPlayeramt);



    //   getPlayers()[game_state.players_amt];
    // game_state.players = (Player*)malloc(game_state.players_amt*sizeof(Player));


    for (i=0; i<getPlayers_amt(); i++) {
        getPlayers()[i].setCash(getStarting_cash());
        getPlayers()[i].setPosition(0);
        getPlayers()[i].setUser_properties(vector <Property>());
        getPlayers()[i].setPlayer_num(i);
        getPlayers()[i].setRoll(false);

    }

    setTurncount(0);
    setPlayer_turn(0);


    file.close();
    file2.close();


}




bool Gamestate::is_game_over() {
    bool game_over = false;

    if (getTurncount()>= getTurn_limit() && getTurn_limit()!=-1){
        game_over = true;
    }

    int players_remaining = 0;
    for (int i = 0; i< getPlayers_amt(); i++){
        if (getPlayers()[i].getPlayer_num() != -1) {
            players_remaining = players_remaining + 1;
        }

    }
    if (players_remaining <= getPlayer_endgame()){
        game_over = true;
    }


    return game_over;

// returns false while certain parameters are met depending on input from rule file
// ie turn limit, number of players left to end game,
// bankruptcy function that autokicks player and forfeits properties
}


void Gamestate::display_game_state(){



    for (int l = 0; l< getSpaceCount(); l++){
        cout << l << " |  " << getProperties()[l].getName() << "\t|\t";
        for (int k = 0 ; k< getPlayers_amt(); k++){
            if (getPlayers()[k].getPosition() == l && getPlayers()[k].getPlayer_num() != -1){
                cout << getPlayers()[k].getPlayer_num() << " ";
            }
        }
        cout << endl;
    }




}




void Gamestate::change_turn() {

    for (int i=0; i<getPlayers_amt(); i++){

        if (getPlayer_turn() <= getPlayers_amt() - 2 &&
            (getPlayers()[getPlayer_turn() + 1].getPlayer_num() != -1)) {
            setPlayer_turn(getPlayer_turn()+1); // increment function
            break;
        } else if (getPlayer_turn() == getPlayers_amt() - 1 && getPlayers()[0].getPlayer_num() != -1) {
            setPlayer_turn(0);
            break;
        }
        else{
            setPlayer_turn(getPlayer_turn()+1);
        }
    }

}


void Gamestate::declare_winners(){
    vector<int> finalWinners;
    int maxPrice = 0;

    int playerwinners[getPlayers_amt()];



    for (int i = 0; i < getPlayers_amt(); i++){
        if (getPlayers()[i].getPlayer_num() != -1) {
            playerwinners[i] = getPlayers()[i].getCash();
            for (uint j = 0; j < getPlayers()[i].getUser_properties().size(); j++) {
                playerwinners[i] += getPlayers()[i].getUser_properties()[j].getPrice();
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
            finalWinners.push_back(k);
        }
    }

    cout << "The winners are " << endl;


    for (uint l = 0; l < finalWinners.size(); l++) {
        cout << "Player " << finalWinners[l] << endl;

    }

}




void Gamestate::delete_game_state(){
    getRandom()->close();



};

int Gamestate::getSpaceCount() const {
    return spaceCount;
}

void Gamestate::setSpaceCount(int spaceCount) {
    Gamestate::spaceCount = spaceCount;
}

Player *Gamestate::getPlayers() const {
    return players;
}

void Gamestate::setPlayers(Player *players) {
    Gamestate::players = players;
}

int Gamestate::getPlayers_amt() const {
    return players_amt;
}

void Gamestate::setPlayers_amt(int players_amt) {
    Gamestate::players_amt = players_amt;
}

int Gamestate::getPlayer_turn() const {
    return player_turn;
}

void Gamestate::setPlayer_turn(int player_turn) {
    Gamestate::player_turn = player_turn;
}

Property *Gamestate::getProperties() const {
    return properties;
}

void Gamestate::setProperties(Property *properties) {
    Gamestate::properties = properties;
}

ifstream  *Gamestate::getRandom() const {
    return random;
}

void Gamestate::setRandom(ifstream *random) {
    Gamestate::random = random;
}


