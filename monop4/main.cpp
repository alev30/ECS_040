#include "Gamestate.h"

using namespace Monopoly;

int main(int argc, char** argv) {
    Gamestate game_state;
    game_state.setup(argv[1], argv[2]);

    DiceRoller roll;
    roll.openRand(argv[3]);



    while(!game_state.isGameOver()){
        do{
            game_state.display_game_state();
            game_state.jailCheck();
            if(game_state.isEnds_turn()){
                break;
            }
            game_state.get_move();
            game_state.make_move(&roll);
        }while(!game_state.isEnds_turn());
        game_state.change_turn();
    }

    game_state.display_game_state();
    game_state.declare_winners();
    roll.close();
    return 0;
}