
#include "Gamestate.h"




int main(int argc, char** argv) {



    Gamestate game_state;
    game_state.setup(argv[1], argv[2]);

    DiceRoller roll;
    roll.openRand(argv[3]);



    while(!game_state.is_game_over()){
        do{
            game_state.display_game_state();
            game_state.get_move(game_state.getPlayer_turn());
            game_state.make_move(&roll);
        }while(!game_state.isEnds_turn());
        game_state.change_turn();
    }

    game_state.display_game_state();
    game_state.declare_winners();
    roll.close();
    return 0;
}