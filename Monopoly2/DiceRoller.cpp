//
// Created by Adam Levin on 2/7/18.
//

#include "DiceRoller.h"

void DiceRoller::close(){

    this->getRandom()->close();
    delete this->random;
};




int DiceRoller::dice_roll(){

    setDoubles(false);

    std::string buffer4;


    std::getline(*getRandom(),buffer4);


    if (buffer4.empty()){
        std::getline(*getRandom(),buffer4);
    }

    std::stringstream tempstring(buffer4);
    int temp_rand_var;
    tempstring >> temp_rand_var;

    std:: cout << temp_rand_var << std::endl;


    temp_rand_var = temp_rand_var%6 + 1;


    std::getline(*getRandom(),buffer4);


    std::stringstream tempstring1(buffer4);
    int temp_rand_var1;
    tempstring1 >> temp_rand_var1;

    if (buffer4.empty()){
        std::getline(*getRandom(),buffer4);
    }

    std::cout<< temp_rand_var1 << std::endl;

    temp_rand_var1 = temp_rand_var1%6 + 1;




    if (temp_rand_var==temp_rand_var1){
        setDoubles(true);
    }



    printf( "you rolled a %d\n",temp_rand_var+temp_rand_var1);
    return temp_rand_var + temp_rand_var1;
}



void DiceRoller::openRand(char* RandomFile){

    std::ifstream *file3 = new std::ifstream(RandomFile);
    setRandom(file3);
}

std::ifstream *DiceRoller::getRandom() const {
    return random;
}

void DiceRoller::setRandom(std::ifstream *random) {
    DiceRoller::random = random;
}

bool DiceRoller::isDoubles() const {
    return doubles;
}

void DiceRoller::setDoubles(bool doubles) {
    DiceRoller::doubles = doubles;
}

