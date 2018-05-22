//
// Created by Adam Levin on 2/26/18.
//

#ifndef MONOPOLY_4_SPACE_H
#define MONOPOLY_4_SPACE_H



#include <string>
#include <iostream>

#include "Player.h"

namespace Monopoly {
    class Space{
    public:
        // getters and setters//
        const std::string &getSpaceType() const;
        void setSpaceType(const std::string &spaceType);
        const std::string &getSpaceName() const;
        void setSpaceName(const std::string &spaceName);
        int getSpaceNum() const;
        void setSpaceNum(int spaceNum);
        // other functions//
        virtual void activate(Monopoly::Player &player) = 0;
        virtual void display() = 0;
    private:
        std::string spaceType;
        std::string spaceName;
        int spaceNum;
    };
}

#endif //MONOPOLY_4_SPACE_H
