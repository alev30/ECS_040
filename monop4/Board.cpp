//
// Created by Adam Levin on 2/26/18.
//

#include "Board.h"

std::vector<std::unique_ptr<Monopoly::Space>> &Monopoly::Board::getboard(){ return board; }
//void Monopoly::Board::setboard(const std::vector<std::unique_ptr<Monopoly::Space>> &board) { Board::board = board; }
int Monopoly::Board::getMaxSetID() const { return maxSetID; }
void Monopoly::Board::setMaxSetID(int maxSetID) { Board::maxSetID = maxSetID; }
int Monopoly::Board::getSpaceCount() const { return spaceCount; }
void Monopoly::Board::setSpaceCount(int spaceCount) { Board::spaceCount = spaceCount; }
int Monopoly::PayBank::getFee() const { return fee; }
void Monopoly::PayBank::setFee(int fee) { PayBank::fee = fee; }
int Monopoly::Jail::getTotalTurns() const { return totalTurns; }
void Monopoly::Jail::setTotalTurns(int totalTurns) { Jail::totalTurns = totalTurns; }
int Monopoly::Jail::getFeeToLeave() const { return feeToLeave; }
void Monopoly::Jail::setFeeToLeave(int feeToLeave) { Jail::feeToLeave = feeToLeave; }
int Monopoly::GoToJail::getJailspace() const { return jailspace; }
void Monopoly::GoToJail::setJailspace(int jailspace) { GoToJail::jailspace = jailspace; }
int Monopoly::FreeParking::getParkingSpots() const { return parkingSpots; }
void Monopoly::FreeParking::setParkingSpots(int parkingSpots) { FreeParking::parkingSpots = parkingSpots; }
int Monopoly::FreeParking::getFpCash() const { return fpCash; }
void Monopoly::FreeParking::setFpCash(int fpCash) { FreeParking::fpCash = fpCash; }
int Monopoly::GoSpace::getGoPay() const { return goPay; }
void Monopoly::GoSpace::setGoPay(int goPay) { GoSpace::goPay = goPay; }

void Monopoly::GoSpace::display() {
    std:: cout << getSpaceNum() << "\t|" << getSpaceName() << "\t|" << "None\t\t||";
}

void Monopoly::GoSpace::activate(Monopoly::Player &player){
    //GoSpace *goSpace = dynamic_cast<GoSpace*>()
    player.setCash (player.getCash() + (player.getGoCash()*player.getGoMultiplier()));
}

void Monopoly::FreeParking::display() {
    std:: cout << getSpaceNum() << "\t|" << getSpaceName() << "\t|"  << "None\t\t||";
}

void Monopoly::FreeParking::activate(Monopoly::Player &player){
    if (getFpCash() > 0) {
        std::cout << player.getPlayerName() << " got $" << getFpCash() << "for landing on " << getSpaceName()
                  << std::endl;
        player.setCash(player.getCash() + getFpCash());
        player.setPayFP(-1 * getFpCash());
        setFpCash(0);
    }
}

void Monopoly::GoToJail::display() {
    std:: cout << getSpaceNum() << "\t|" << getSpaceName() << "\t|" << "None\t\t||";
}

void Monopoly::GoToJail::activate(Monopoly::Player &player){
    player.setJustVisiting(false);
    player.setPosition(getJailspace());
    player.setFirstTurnInJail(true);
    player.setSentToJail(true);
}

void Monopoly::Jail::display() {
    std:: cout << getSpaceNum() << "\t|" << getSpaceName() << "\t|" << "None\t\t||";
}

void Monopoly::Jail::activate(Monopoly::Player &player){
    int subsetVal = 0;
    int downGradeChoice = 0;
    int increment;
    if(player.isJustVisiting()){
        // do nothing //
    }
    else {
        // JAILTIME MOFOS //
        // set jail turns //
        if (player.isFirstTurnInJail()) {
            player.setTurnsInJail(getTotalTurns());
            player.setFirstTurnInJail(false);
            player.setSentToJail(false);
        }

        else if(player.getTurnsInJail() == 0) {
            // must pay fee //
            if (player.getCash() > getFeeToLeave()) {
                if (player.isFreeParking()){
                    player.setPayFP(getFeeToLeave());
                    player.setCash(player.getCash() - getFeeToLeave());
                    std::cout <<player.getPlayerName() << ", you had to pay $" <<getFeeToLeave() << " to get out of jail" << std::endl;
                    player.setJustVisiting(true);
                }
                else {
                    player.setCash(player.getCash() - getFeeToLeave());
                    std::cout <<player.getPlayerName() << ", you had to pay $" <<getFeeToLeave() << " to get out of jail" << std::endl;
                    player.setJustVisiting(true);
                }
            }
            else {
                // sell any upgrades on their properties to leave //   *****NEED TO IMPLEMENT******
                if (player.isUpgradeOwner()) {
                    while (player.getCash() < getFeeToLeave()) {
                        player.setHasDowngraded(true);
                        std::cout << "You must downgrade properties in order to not go bankrupt" << std::endl;
                        std::cout << "Which property do you want to downgrade?" << std::endl;
                        for (int i = 0; i < (unsigned short) player.getUser_properties().size(); i++) {
                            if (player.getUser_properties()[i].isHasUpgrades()) {
                                std::cout << subsetVal << ". " << player.getUser_properties()[i].getSpaceName()
                                          << " [$";
                                if (player.getUser_properties()[i].getHouses() > 0) {
                                    std::cout << player.getUser_properties()[i].getHouseCost() / 2 << "]" << std::endl;
                                } else {
                                    std::cout << player.getUser_properties()[i].getHotelCost() / 2 << "]" << std::endl;
                                }
                                subsetVal++;
                            }
                        }

                        std::cout << "Your choice: ";
                        std::cin >> downGradeChoice;
                        increment = 0;
                        for (int i = 0; i < (unsigned short) player.getUser_properties().size(); i++) {
                            if (player.getUser_properties()[i].isHasUpgrades()) {
                                if (downGradeChoice == increment && player.getUser_properties()[i].getHouses() > 0) {
                                    player.setCash(
                                            player.getCash() + player.getUser_properties()[i].getHouseCost() / 2);
                                    player.getUser_properties()[i].setHouses(
                                            player.getUser_properties()[i].getHouses() - 1);
                                }
                                else if(downGradeChoice == increment && player.getUser_properties()[i].getHotels() > 0) {
                                    player.setCash(
                                            player.getCash() + player.getUser_properties()[i].getHotelCost() / 2);
                                    player.getUser_properties()[i].setHotels(
                                            player.getUser_properties()[i].getHotels() - 1);
                                    player.getUser_properties()[i].setHouses(player.getHousesb4hotels());
                                }
                                if (downGradeChoice == increment && player.getUser_properties()[i].getHouses() == 0){
                                    player.getUser_properties()[i].setHasUpgrades(false);
                                }
                                increment++;
                            }
                        }
                        subsetVal = 0;
                        for (int l = 0; l < (unsigned short) player.getUser_properties().size(); l++){
                            if (player.getUser_properties()[l].isHasUpgrades()){
                                subsetVal++;
                            }
                        }
                        if (subsetVal == 0){
                            player.setUpgradeOwner(false);
                            break;
                        }
                    }
                    if (player.getCash() < getFeeToLeave()){
                        std::cout << player.getPlayerName() << " went bankrupt when paying to leave jail" << std::endl;
                        player.setBankrupt(true);
                    }
                    else{
                        if (player.isFreeParking()){
                            player.setPayFP(getFeeToLeave());
                            player.setCash(player.getCash() - getFeeToLeave());
                        }
                        else {
                            player.setCash(player.getCash() - getFeeToLeave());
                        }
                    }
                }

                else {
                    std::cout << player.getPlayerName() << " went bankrupt when paying to leave jail" << std::endl;
                    player.setBankrupt(true);
                }

            }
        }
        else if (player.getTurnsInJail()> 0){
            player.setTurnsInJail(player.getTurnsInJail()-1);
        }
    }
}

void Monopoly::PayBank::display() {
    std:: cout << getSpaceNum() << "\t|" << getSpaceName() << "\t|" << "None\t\t||";
}


void Monopoly::PayBank::activate(Monopoly::Player &player){

    if (player.getCash() >= getFee()) {
        player.setPayFP(getFee());
        player.setCash(player.getCash() - getFee());
        std::cout << player.getPlayerName() << " paid the bank $" << getFee() << " for landing on " << getSpaceName()
                  << std::endl;
    }
    else{
        std::cout << player.getPlayerName() << " went bankrupt by landing on " << getSpaceName() << std::endl;
        player.setPayFP(player.getCash());
        player.setCash(0);
        player.setBankrupt(true);
    }
}

void Monopoly::Board::BoardSetup(char *BoardFile) {

    std::ifstream file2(BoardFile);
    std::string buffer2 = "";
    int i = 1;
    while (std::getline(file2, buffer2)) { i = i + 1; }
    file2.clear();
    file2.seekg(0, std::ios::beg);
    spaceCount = i-5;
    for (i = 0; i < 4; ++i) {
        getline(file2, buffer2);
    }
    board.push_back(std::make_unique<Monopoly::GoSpace>());
   // Monopoly::GoSpace Go;
    // generate Go space//
    std::getline(file2, buffer2, ',');
    static_cast<GoSpace*>(board[0].get())->setSpaceType(buffer2);
    //Go.setSpaceType(buffer2);
    std::getline(file2, buffer2, ',');
    static_cast<GoSpace*>(board[0].get())->setGoPay(stoi(buffer2));
    setPassGoCash(stoi(buffer2));
    //Go.setGoPay(std::stoi(buffer2));
    std::getline(file2, buffer2, ',');
    static_cast<GoSpace*>(board[0].get())->setSpaceName(buffer2);
    static_cast<GoSpace*>(board[0].get())->setSpaceNum(0);

    //Go.setSpaceName(buffer2);
    //Go.setSpaceNum(0);
    //*board[0] = Go;

    for (int k = 0; k < 6; k++) {
        getline(file2, buffer2, ',');
    }
    setMaxSetID(0);
    setTotalFPCash(0);
    int COLUMNS = 10;
    std::string type;

    std::getline(file2,buffer2);
    // generate rest of board //
    for (i = 1; i< spaceCount; i++){
        std::getline(file2, buffer2, ',');
        type = buffer2;
        // generate property type //
        if (type == "Property"){
            board.push_back(std::make_unique<Monopoly::Property>());
            //Monopoly::Property prop;
            for (int j = 1; j < COLUMNS - 1; j++) {
                static_cast<Property*>(board[i].get())->setSpaceType(type);
                getline(file2, buffer2, ',');
                switch (j) {
                    case 1:
                        static_cast<Property*>(board[i].get())->setSetID(stoi(buffer2));
                        break;
                    case 2:
                        static_cast<Property*>(board[i].get())->setSubSetID(stoi(buffer2));
                        break;
                    case 3:
                        static_cast<Property*>(board[i].get())->setSpaceName(buffer2);
                        break;
                    case 4:
                        static_cast<Property*>(board[i].get())->setPrice(stoi(buffer2));
                        break;
                    case 5:
                        static_cast<Property*>(board[i].get())->setHouseCost(stoi(buffer2));
                        break;
                    case 6:
                        static_cast<Property*>(board[i].get())->setHotelCost(stoi(buffer2));
                        break;
                    case 7:
                        static_cast<Property*>(board[i].get())->setNormalRent(stoi(buffer2));
                        break;
                    case 8:
                        static_cast<Property*>(board[i].get())->setHouseRent(stoi(buffer2));
                        break;
                    case 9:
                        static_cast<Property*>(board[i].get())->setHotelRent(stoi(buffer2));
                        break;
                }
            }
            static_cast<Property*>(board[i].get())->setPropertyOwnerName("");
            static_cast<Property*>(board[i].get())->setHasUpgrades(false);
            static_cast<Property*>(board[i].get())->setPropertySet(false);
            static_cast<Property*>(board[i].get())->setOwner(-1);
            static_cast<Property*>(board[i].get())->setHouses(0);
            static_cast<Property*>(board[i].get())->setHotels(0);
            static_cast<Property*>(board[i].get())->setSpaceNum(i);
            static_cast<Property*>(board[i].get())->setMostUpgrades(false);
            if (static_cast<Property*>(board[i].get())->getSetID()>getMaxSetID()){
                setMaxSetID(static_cast<Property*>(board[i].get())->getSetID());
            }
            //*board[i] = prop;
        }
        // generate freeParking //
        else if (type == "FreeParking"){
            board.push_back(std::make_unique<Monopoly::FreeParking>());
            std::getline(file2, buffer2, ',');
            //Monopoly::FreeParking FP;
            static_cast<FreeParking*>(board[i].get())->setSpaceType(type);
            static_cast<FreeParking*>(board[i].get())->setSpaceName(buffer2);
            static_cast<FreeParking*>(board[i].get())->setFpCash(0);
            static_cast<FreeParking*>(board[i].get())->setSpaceNum(i);
            FPspaceCount++;
            //*board[i] = FP;
        }
        // generate PayBank //
        else if (type == "Pay"){
            board.push_back(std::make_unique<Monopoly::PayBank>());
            //Monopoly::PayBank pb;
            static_cast<PayBank*>(board[i].get())->setSpaceType(type);
            static_cast<PayBank*>(board[i].get())->setSpaceNum(i);
            std::getline(file2, buffer2, ',');
            static_cast<PayBank*>(board[i].get())->setSpaceName(buffer2);
            std::getline(file2, buffer2, ',');
            static_cast<PayBank*>(board[i].get())->setFee(std::stoi(buffer2));
            //*board[i] = pb;
        }
        // generate GoToJail //
        else if (type == "GoToJail"){
            board.push_back(std::make_unique<Monopoly::GoToJail>());
            //Monopoly::GoToJail g2j;
            static_cast<GoToJail*>(board[i].get())->setSpaceNum(i);
            static_cast<GoToJail*>(board[i].get())->setSpaceType(type);
            std::getline(file2, buffer2, ',');
            static_cast<GoToJail*>(board[i].get())->setSpaceName(buffer2);
            std::getline(file2, buffer2, ',');
            static_cast<GoToJail*>(board[i].get())->setJailspace(std::stoi(buffer2));
            //*board[i] = g2j;
        }
        // generate Jail //
        else if (type == "Jail"){
            board.push_back(std::make_unique<Monopoly::Jail>());
            //Monopoly::Jail jail;
            static_cast<Jail*>(board[i].get())->setSpaceType(type);
            static_cast<Jail*>(board[i].get())->setSpaceNum(i);
            std::getline(file2, buffer2, ',');
            static_cast<Jail*>(board[i].get())->setSpaceName(buffer2);
            std::getline(file2, buffer2, ',');
            static_cast<Jail*>(board[i].get())->setTotalTurns(std::stoi(buffer2));
            std::getline(file2, buffer2, ',');
            static_cast<Jail*>(board[i].get())->setFeeToLeave(std::stoi(buffer2));
            //*board[i] = jail;
        }
        getline(file2, buffer2);
    }

}

int Monopoly::Board::getPassGoCash() const {
    return passGoCash;
}

void Monopoly::Board::setPassGoCash(int passGoCash) {
    Board::passGoCash = passGoCash;
}

int Monopoly::Board::getFPspaceCount() const {
    return FPspaceCount;
}

void Monopoly::Board::setFPspaceCount(int FPspaceCount) {
    Board::FPspaceCount = FPspaceCount;
}

int Monopoly::Board::getTotalFPCash() const {
    return totalFPCash;
}

void Monopoly::Board::setTotalFPCash(int totalFPCash) {
    Board::totalFPCash = totalFPCash;
}

