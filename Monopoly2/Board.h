//
// Created by Adam Levin on 2/7/18.
//

#ifndef BOARD_H
#define BOARD_H


#include "Property.h"

class Board{
private:
    int maxSetID;
    std::vector<Property>propertySet;
    int spaceCount;
public:
    int getSpaceCount() ;

    void setSpaceCount(int spaceCount);

    void boardSetup(char* BoardFile);

    std::vector<Property> &getPropertySet();

    void setPropertySet(std::vector<Property> &propertySet);

    int getMaxSetID() ;

    void setMaxSetID(int maxSetID);

    void addProperty(Property aProperty);

};


#endif
