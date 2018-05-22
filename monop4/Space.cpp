//
// Created by Adam Levin on 2/26/18.
//

#include "Space.h"

//getters and setters//

const std::string &Monopoly::Space::getSpaceType() const { return spaceType; }
void Monopoly::Space::setSpaceType(const std::string &spaceType) { Space::spaceType = spaceType; }
const std::string &Monopoly::Space::getSpaceName() const { return spaceName; }
void Monopoly::Space::setSpaceName(const std::string &spaceName) { Space::spaceName = spaceName; }
int Monopoly::Space::getSpaceNum() const { return spaceNum; }
void Monopoly::Space::setSpaceNum(int spaceNum) { Space::spaceNum = spaceNum; }

//other functions//

//virtual void Monopoly::Space::activate(Monopoly::Player &player) = 0;
/*void Monopoly::Space::display(){
    std::cout<< spaceNum << "\t|" << spaceName << "\t|";
}*/


