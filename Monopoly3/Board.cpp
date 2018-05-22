//
// Created by Adam Levin on 2/7/18.
//

#include "Board.h"

int Board::getMaxSetID() const {
    return maxSetID;
}

void Board::setMaxSetID(int maxSetID) {
    Board::maxSetID = maxSetID;
}
