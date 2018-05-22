//
// Created by Adam Levin on 2/7/18.
//

#include "Board.h"

int Board::getMaxSetID()  {
    return maxSetID;
}

void Board::setMaxSetID(int maxSetID) {
    Board::maxSetID = maxSetID;
}




void Board::boardSetup(char *BoardFile) {
 //       Board board;
 //       Property property;

        std::ifstream file2(BoardFile);
        std::string buffer2 = "";

        int i = 1;

        while (std::getline(file2, buffer2)) {

            i = i + 1;

        }


        file2.clear();
        file2.seekg(0, std::ios::beg);

         int BOARD_SPACES = i - 5;

        std::vector <Property> propBoard (BOARD_SPACES);

        this->setSpaceCount(BOARD_SPACES);




        for (i = 0; i < 4; ++i) {
            getline(file2, buffer2);
        }


         int COLUMNS = 10;
        std::getline(file2, buffer2, ',');
        propBoard[0].setType(buffer2);
        getline(file2, buffer2, ',');
        propBoard[0].setPrice(stoi(buffer2));

        getline(file2, buffer2, ',');
        propBoard[0].setName(buffer2);
        propBoard[0].setOwner(-2);
        propBoard[0].setSpaceNum(0);
        for (int k = 0; k < 6; k++) {
            getline(file2, buffer2, ',');
        }

        this->setMaxSetID(0);
// the below for loop starts at line 6, which is where the go space starts
        for (i = 1; i < BOARD_SPACES; i++) {


            for (int j = 0; j < COLUMNS - 1; j++) {


                getline(file2, buffer2, ',');

                switch (j) {
                    case 0:
                        propBoard[i].setType(buffer2);
                        break;

                    case 1:

                        propBoard[i].setSetID(stoi(buffer2));
                        break;

                    case 2:
                        propBoard[i].setSubsetID(stoi(buffer2));
                        break;
                    case 3:
                        propBoard[i].setName(buffer2);

                        break;

                    case 4:
                        propBoard[i].setPrice(stoi(buffer2));
                        break;
                    case 5:
                        propBoard[i].setHouse_cost(stoi(buffer2));
                        break;
                    case 6:
                        propBoard[i].setHotel_cost(stoi(buffer2));
                        break;
                    case 7:
                        propBoard[i].setRent(stoi(buffer2));
                        break;
                    case 8:
                        propBoard[i].setRent_with_house(stoi(buffer2));
                        break;
                    case 9:
                        propBoard[i].setRent_with_hotel(stoi(buffer2));
                        break;

                }

            }

            propBoard[i].setOwner(-1);
            propBoard[i].setHouses(0);
            propBoard[i].setHotels(0);
            propBoard[i].setSpaceNum(i);
            if (propBoard[i].getSetID()>this->getMaxSetID()){
                this->setMaxSetID(propBoard[i].getSetID());
            }

        }
        file2.close();



        this->setPropertySet(propBoard);

}

 std::vector<Property> &Board::getPropertySet()  {
    return propertySet;
}

void Board::setPropertySet( std::vector<Property> &propertySet) {
    Board::propertySet = propertySet;
}

void Board::addProperty(Property aProperty){
    getPropertySet().push_back(aProperty);

}

int Board::getSpaceCount()  {
    return spaceCount;
}

void Board::setSpaceCount(int spaceCount) {
    Board::spaceCount = spaceCount;
}




