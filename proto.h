#ifndef _TWIXT_GAME_H_
#define _TWIXT_GAME_H_

#include <stdbool.h>
#include <stdio.h>

#define DIM 24
#define MAX_LINKS 1024
#define MAX_Q 576

#define FOR_GRID(i) for(int i=0; i<DIM; i++)
#define CLAMP(x) ((x) < 0 ? 0 : ((x) >= DIM ? DIM-1 : (x)))

#define T_RED 1
#define T_BLK 2

typedef enum {
    OP_PLACE, OP_LINK, OP_CUT, OP_PASS, OP_HELP, OP_SHOW, OP_QUIT, OP_BAD
} CmdType;

typedef struct {
    int r, c; 
} Point;

typedef struct {
    Point u, v;
} Link;

typedef struct {
    int map[DIM][DIM]; 
    Link links[MAX_LINKS];
    int n_links;
    int turn; 
    bool game_over;
    int winner;
} TwixtBoard;

typedef struct {
    CmdType type;
    int r1, c1, r2, c2;
} UserCmd;

void reset_board(TwixtBoard *tb);
bool try_place(TwixtBoard *tb, int r, int c);
bool try_link(TwixtBoard *tb, Point p1, Point p2);
bool try_cut(TwixtBoard *tb, Point p1, Point p2);
bool check_win(TwixtBoard *tb);
void next_turn(TwixtBoard *tb);

void cls();
void render(TwixtBoard *tb);
void hud(TwixtBoard *tb);
void msg(const char *txt, int lvl); 
void loop_game(TwixtBoard *tb);

#endif