//
// Created by Adam Levin on 2/26/18.
//

#ifndef MONOPOLY_4_BOARD_H
#define MONOPOLY_4_BOARD_H

#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

#include "Space.h"
#include "Property.h"
#include "Rules.h"

namespace Monopoly {
    class PayBank : public Space{
    public:
        int getFee() const;
        void setFee(int fee);
        void activate(Monopoly::Player &player);
        void display();
    private:
        int fee;
    };

    class Jail : public Space{
    public:
        int getTotalTurns() const;
        void setTotalTurns(int totalTurns);
        int getFeeToLeave() const;
        void setFeeToLeave(int feeToLeave);
        void activate(Monopoly::Player &player);
        void display();
    private:
        int totalTurns;
        int feeToLeave;
    };

    class GoToJail : public Space{
    public:
        int getJailspace() const;
        void setJailspace(int jailspace);
        void activate(Monopoly::Player &player);
        void display();
    private:
        int jailspace;
    };

    class FreeParking : public Space{
    public:
        int getParkingSpots() const;
        void setParkingSpots(int parkingSpots);
        void activate(Monopoly::Player &player);
        int getFpCash() const;
        void setFpCash(int fpCash);
        void display();

    private:
        int parkingSpots;
        int fpCash;
    };

    class GoSpace : public Space{
    public:
        int getGoPay() const;
        void setGoPay(int goPay);
        void activate(Monopoly::Player &player);
        void display();
    private:
        int goPay;
    };

    class Board{
    public:
        int getTotalFPCash() const;
        void setTotalFPCash(int totalFPCash);
        int getFPspaceCount() const;
        void setFPspaceCount(int FPspaceCount);
        int getMaxSetID() const;
        void setMaxSetID(int maxSetID);
        int getSpaceCount() const;
        void setSpaceCount(int spaceCount);
        std::vector<std::unique_ptr<Space>> &getboard();
        //void setboard(const std::vector<std::unique_ptr<Space>> &board);
        int getPassGoCash() const;
        void setPassGoCash(int passGoCash);
        void BoardSetup(char* BoardFile);

    private:
        int totalFPCash;
        int FPspaceCount;
        int passGoCash;
        std::vector<std::unique_ptr<Monopoly::Space>> board;
        int maxSetID;
        int spaceCount;
    };
}


#endif //MONOPOLY_4_BOARD_H
