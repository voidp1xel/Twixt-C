#include "proto.h"
#include <stdlib.h>

void cls() {
    system("cls || clear");
}

void msg(const char *txt, int lvl) {
    const char *col = (lvl == 2) ? "\033[1;31m" : (lvl == 1 ? "\033[1;32m" : "\033[1;36m");
    printf("  %s>> %s\033[0m\n", col, txt);
}

void render(TwixtBoard *tb) {
    printf("\n    ");
    for (int i = 0; i < DIM; i++) {
        if (i < 10) printf(" %d ", i);
        else printf("%-3d", i);
    }
    printf("\n");

    // Top border
    printf("    \033[1;31m");
    for (int i = 0; i < DIM; i++) printf("---");
    printf("\033[0m\n");

    for (int r = 0; r < DIM; r++) {
        printf("\033[1;33m%2d\033[0m \033[1;36m|\033[0m", r);

        for (int c = 0; c < DIM; c++) {
            int cell = tb->map[r][c];
            
            bool r_bound = (r == 0 || r == DIM-1);
            bool c_bound = (c == 0 || c == DIM-1);

            if (cell == T_RED) {
                printf("\033[1;31m ● \033[0m"); // Red Peg
            } 
            else if (cell == T_BLK) {
                printf("\033[1;36m ● \033[0m"); // Black Peg (Cyan)
            } 
            else {
                if (r_bound && c_bound) printf("   "); 
                else if (r_bound) printf("\033[31m - \033[0m"); // Red boundary
                else if (c_bound) printf("\033[36m | \033[0m"); // Black boundary
                else printf(" · "); // Empty hole
            }
        }
        printf("\033[1;36m|\033[0m\n");
    }

    // Bottom border
    printf("    \033[1;31m");
    for (int i = 0; i < DIM; i++) printf("---");
    printf("\033[0m\n");
}

void hud(TwixtBoard *tb) {
    printf("\n \033[1;37m[ TURN: %s ]\033[0m", tb->turn == T_RED ? "\033[1;31mRED (#)\033[0m" : "\033[1;36mBLACK (@)\033[0m");
    printf("  \033[1;32mLinks: %d\033[0m\n", tb->n_links);
    printf(" \033[1;30m--------------------------------------------------------------\033[0m\n");
}