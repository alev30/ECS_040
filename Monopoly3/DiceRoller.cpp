//
// Created by Adam Levin on 2/7/18.
//

#include "DiceRoller.h"



int DiceRoller::dice_roll(Gamestate*gamestate){


    string buffer4;
    getline(*gamestate->getRandom(),buffer4);

    stringstream tempstring(buffer4);
    int temp_rand_var;
    tempstring >> temp_rand_var;
    temp_rand_var = temp_rand_var%6 + 1;
    getline(*gamestate->getRandom(),buffer4);


    stringstream tempstring1(buffer4);
    int temp_rand_var1;
    tempstring1 >> temp_rand_var1;
    temp_rand_var1 = temp_rand_var1%6 + 1;

    cout << "You rolled a " << temp_rand_var+temp_rand_var1 << "!" <<endl;
    return temp_rand_var + temp_rand_var1;
}