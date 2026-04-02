#include "proto.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void trim(char *s) {
    if (!s) return;
    int len = strlen(s);
    while(len > 0 && isspace(s[len-1])) {
        s[len-1] = '\0';
        len--;
    }
}

UserCmd get_cmd(const char *raw) {
    UserCmd c = {OP_BAD, 0, 0, 0, 0};
    char buf[256];
    strncpy(buf, raw, 255);
    buf[255] = '\0';
    trim(buf);
    
    if(!*buf) return c;

    char *tok = strtok(buf, " \t");
    if(!tok) return c;

    char code = tolower(tok[0]); 

    #define GET_NEXT_INT(var) { \
        char *nxt = strtok(NULL, " \t"); \
        var = nxt ? atoi(nxt) : 0; \
    }

    switch(code) {
        case 'p': 
            c.type = OP_PLACE;
            GET_NEXT_INT(c.r1);
            GET_NEXT_INT(c.c1);
            break;
        case 'l': 
            c.type = OP_LINK;
            GET_NEXT_INT(c.r1);
            GET_NEXT_INT(c.c1);
            GET_NEXT_INT(c.r2);
            GET_NEXT_INT(c.c2);
            break;
        case 'u': 
            c.type = OP_CUT;
            GET_NEXT_INT(c.r1);
            GET_NEXT_INT(c.c1);
            GET_NEXT_INT(c.r2);
            GET_NEXT_INT(c.c2);
            break;
        case 'd':
            c.type = OP_PASS;
            break;
        case 'h':
            c.type = OP_HELP;
            break;
        case 's':
            c.type = OP_SHOW;
            break;
        case 'q':
            c.type = OP_QUIT;
            break;
    }
    return c;
}

void loop_game(TwixtBoard *tb) {
    char input[256];
    bool acted = false;

    while(1) {
        printf("\033[1;33mAction>\033[0m ");
        if(!fgets(input, sizeof(input), stdin)) break;

        UserCmd cmd = get_cmd(input);

        if (cmd.type == OP_QUIT) {
            printf("\033[1;31mGame Exited.\033[0m\n");
            exit(0);
        }

        if (cmd.type == OP_SHOW) {
            cls(); render(tb); hud(tb);
            continue;
        }

        if (cmd.type == OP_HELP) {
            printf("\033[1;37mCommands:\033[0m\n");
            printf("  \033[1;32mp r c\033[0m          - Place a peg atRow r, Col c\n");
            printf("  \033[1;32ml r1 c1 r2 c2\033[0m - Link two pegs\n");
            printf("  \033[1;32mu r1 c1 r2 c2\033[0m - Unlink (cut) two pegs\n");
            printf("  \033[1;32mdone / d\033[0m      - Finish turn\n");
            printf("  \033[1;32mshow / s\033[0m      - Redraw board\n");
            printf("  \033[1;32mquit / q\033[0m      - Exit game\n");
            continue;
        }

        if (cmd.type == OP_PASS) {
            if(!acted) msg("You must place a peg before finishing your turn!", 2);
            else return;
            continue;
        }

        if (cmd.type == OP_PLACE) {
            if(acted) { msg("Only one peg allowed per turn.", 2); continue; }
            
            if(try_place(tb, cmd.r1, cmd.c1)) {
                acted = true;
                cls(); render(tb); hud(tb);
                msg("Peg placed successfully.", 1);
            } else {
                msg("Invalid position! Check the coordinates and boundaries.", 2);
            }
        } 
        else if (cmd.type == OP_LINK || cmd.type == OP_CUT) {
            // Can link multiple times after placing a peg
            if(!acted) { msg("Place a peg first!", 2); continue; }
            
            Point a = {cmd.r1, cmd.c1};
            Point b = {cmd.r2, cmd.c2};

            if(cmd.type == OP_LINK) {
                if(try_link(tb, a, b)) {
                    cls(); render(tb); hud(tb);
                    msg("Linked!", 1);
                } else msg("Invalid link! Distance must be a knight's move and cannot cross other links.", 2);
            } else {
                if(try_cut(tb, a, b)) {
                    cls(); render(tb); hud(tb);
                    msg("Link removed.", 1);
                } else msg("Link not found at specified coordinates.", 2);
            }
        } else {
            msg("Unknown command. Type 'h' for help.", 2);
        }
    }
}