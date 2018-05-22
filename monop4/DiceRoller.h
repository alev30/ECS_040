//
// Created by Adam Levin on 2/26/18.
//

#ifndef MONOPOLY_4_DICEROLLER_H
#define MONOPOLY_4_DICEROLLER_H


#include <fstream>
#include <sstream>

namespace Monopoly {
    class DiceRoller {
    private:
        std::ifstream *random;
        bool doubles;
    public:
        bool isDoubles() const;

        void setDoubles(bool doubles);

        void close();

        int dice_roll();

        void openRand(char *RandomFile);

        std::ifstream *getRandom() const;

        void setRandom(std::ifstream *random);
    };
}

#endif //MONOPOLY_4_DICEROLLER_H
