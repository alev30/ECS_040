//
// Created by Adam Levin on 2/26/18.
//

#ifndef MONOPOLY_4_GAMESTATE_H
#define MONOPOLY_4_GAMESTATE_H

#include "Board.h"
#include "DiceRoller.h"

namespace Monopoly {
    class Gamestate {
    public:
        // gameplay functions //
        void setup(char* rulefile, char* boardfile);
        bool isGameOver();
        void make_move(DiceRoller *roll);
        void get_move();
        void display_game_state();
        void change_turn();
        void declare_winners();
        void jailCheck();
        // getters and setters //
        int getPlayers_amt() const;
        void setPlayers_amt(int players_amt);
        int getPlayer_turn() const;
        void setPlayer_turn(int player_turn);
        bool isEnds_turn() const;
        void setEnds_turn(bool ends_turn);
        int getChoice() const;
        void setChoice(int choice);
        int getTurnCount() const;
        void setTurnCount(int turnCount);
    private:
        std::vector<std::unique_ptr<Monopoly::Player>> players;
        std::unique_ptr<Monopoly::Rules> rules;
        std::unique_ptr<Monopoly::Board> bigboard;
        int players_amt;
        int player_turn;
        bool ends_turn;
        int choice;
        int turnCount;
    };
}


#endif //MONOPOLY_4_GAMESTATE_H
