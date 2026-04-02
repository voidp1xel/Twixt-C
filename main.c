#include "proto.h"

int main() {
    TwixtBoard game;
    
    reset_board(&game);
    cls();
    printf("\033[1;36m");
    printf("==========================================\n");
    printf("        TWIXT GAME ENGINE v2.0            \n");
    printf("==========================================\n");
    printf("\033[0m");
    printf("\nRed must connect Left to Right.\n");
    printf("Black must connect Top to Bottom.\n");
    printf("\nPress [Enter] to Start...");
    getchar();

    while (!game.game_over) {
        cls();
        render(&game);
        hud(&game);

        loop_game(&game);

        if (check_win(&game)) {
            cls();
            render(&game);
            printf("\n\033[1;32m🎉 GAME OVER! 🎉\033[0m\n");
            printf("Winner: \033[1;37m%s\033[0m\n\n", game.winner == T_RED ? "\033[1;31mRED\033[0m" : "\033[1;36mBLACK\033[0m");
            break;
        }

        next_turn(&game);
    }

    return 0;
}