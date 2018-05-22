//
// Created by Adam Levin on 2/7/18.
//

#ifndef RANDOM_H
#define RANDOM_H

#include "Gamestate.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>

class DiceRoller {
public:
    int dice_roll(Gamestate* gamestate);
};


#endif
