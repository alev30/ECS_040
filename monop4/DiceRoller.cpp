//
// Created by Adam Levin on 2/26/18.
//

#include "DiceRoller.h"






int Monopoly::DiceRoller::dice_roll(){


    int die1, die2;
    *random >> die1 >> die2;

    setDoubles(false);

    //std::string buffer4;


    //std::getline(*getRandom(),buffer4);


    /*if (buffer4.empty() || buffer4==NULL || buffer4==""){
        std::getline(*getRandom(),buffer4);
    }*/

    //std::stringstream tempstring(buffer4);
    //int temp_rand_var;
    //tempstring >> temp_rand_var;

    die1 = die1%6+1;
    die2 = die2%6+1;

    //temp_rand_var = temp_rand_var%6 + 1;


    //std::getline(*getRandom(),buffer4);




    //std::stringstream tempstring1(buffer4);
    //int temp_rand_var1;
    //tempstring1 >> temp_rand_var1;




    //temp_rand_var1 = temp_rand_var1%6 + 1;




    if (die1==die2){
        setDoubles(true);
    }




    return die1+die2;
}



void Monopoly::DiceRoller::openRand(char* RandomFile){

    auto *file3 = new std::ifstream(RandomFile);
    setRandom(file3);
}



bool Monopoly::DiceRoller::isDoubles() const {
    return doubles;
}

void Monopoly::DiceRoller::setDoubles(bool doubles) {
    DiceRoller::doubles = doubles;
}

std::ifstream *Monopoly::DiceRoller::getRandom() const {
    return random;
}

void Monopoly::DiceRoller::setRandom(std::ifstream *random) {
    DiceRoller::random = random;
}

void Monopoly::DiceRoller::close(){

    this->getRandom()->close();
    delete this->random;
};