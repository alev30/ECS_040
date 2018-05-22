//
// Created by Adam Levin on 2/7/18.
//

#ifndef DICEROLLER_H
#define DICEROLLER_H


#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>

class DiceRoller {
private:
    std::ifstream* random;
    bool doubles;
public:
    bool isDoubles() const;

    void setDoubles(bool doubles);

    void close();

    int dice_roll();

    void openRand(char* RandomFile);

    std::ifstream *getRandom() const;

    void setRandom(std::ifstream *random);
};


#endif //MONOPOLY_2_RANDOM_H
