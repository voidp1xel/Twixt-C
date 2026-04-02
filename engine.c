#include "proto.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

static int dist_sq(Point p1, Point p2) {
    return (p1.r - p2.r)*(p1.r - p2.r) + (p1.c - p2.c)*(p1.c - p2.c);
}

void reset_board(TwixtBoard *tb) {
    memset(tb->map, 0, sizeof(tb->map));
    tb->n_links = 0;
    tb->turn = T_RED;
    tb->game_over = false;
    tb->winner = 0;
}

bool valid_spot(int r, int c, int team) {
    if (r < 0 || r >= DIM || c < 0 || c >= DIM) return false;

    if ((r==0 || r==DIM-1) && (c==0 || c==DIM-1)) return false;

    if (team == T_RED && (r == 0 || r == DIM-1)) return false;
    if (team == T_BLK && (c == 0 || c == DIM-1)) return false;

    return true;
}

bool try_place(TwixtBoard *tb, int r, int c) {
    if (!valid_spot(r, c, tb->turn)) return false;
    if (tb->map[r][c] != 0) return false;

    tb->map[r][c] = tb->turn;
    return true;
}

static bool intersect(Point a, Point b, Point c, Point d) {
    if ((a.r==c.r && a.c==c.c) || (a.r==d.r && a.c==d.c) ||
        (b.r==c.r && b.c==c.c) || (b.r==d.r && b.c==d.c)) return false;

    double x1=a.c, y1=a.r, x2=b.c, y2=b.r;
    double x3=c.c, y3=c.r, x4=d.c, y4=d.r;

    double det = (y4-y3)*(x2-x1) - (x4-x3)*(y2-y1);
    if (fabs(det) < 1e-7) return false; 

    double ua = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / det;
    double ub = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / det;

    return (ua > 0.001 && ua < 0.999 && ub > 0.001 && ub < 0.999);
}

bool try_link(TwixtBoard *tb, Point p1, Point p2) {
    if (p1.r < 0 || p1.r >= DIM || p1.c < 0 || p1.c >= DIM) return false;
    if (p2.r < 0 || p2.r >= DIM || p2.c < 0 || p2.c >= DIM) return false;
    
    if (tb->map[p1.r][p1.c] != tb->turn || tb->map[p2.r][p2.c] != tb->turn) return false;

    if (dist_sq(p1, p2) != 5) return false;

    for (int i = 0; i < tb->n_links; i++) {
        Link l = tb->links[i];

        bool match = (l.u.r == p1.r && l.u.c == p1.c && l.v.r == p2.r && l.v.c == p2.c);
        bool rev   = (l.u.r == p2.r && l.u.c == p2.c && l.v.r == p1.r && l.v.c == p1.c);
        if (match || rev) return false;
        
        if (intersect(p1, p2, l.u, l.v)) return false;
    }

    if (tb->n_links >= MAX_LINKS) return false;

    tb->links[tb->n_links++] = (Link){p1, p2};
    return true;
}

bool try_cut(TwixtBoard *tb, Point p1, Point p2) {
    if (p1.r < 0 || p1.r >= DIM || p1.c < 0 || p1.c >= DIM) return false;
    if (p2.r < 0 || p2.r >= DIM || p2.c < 0 || p2.c >= DIM) return false;

    for (int i = 0; i < tb->n_links; i++) {
        Link *l = &tb->links[i]; 
        bool fwd = (l->u.r == p1.r && l->u.c == p1.c && l->v.r == p2.r && l->v.c == p2.c);
        bool bwd = (l->u.r == p2.r && l->u.c == p2.c && l->v.r == p1.r && l->v.c == p1.c);
        
        if (fwd || bwd) {
            tb->links[i] = tb->links[--tb->n_links]; 
            return true;
        }
    }
    return false;
}

bool check_win(TwixtBoard *tb) {
    int seen[DIM][DIM] = {0};
    Point queue[MAX_Q];
    int q_in = 0, q_out = 0;
    int me = tb->turn;

    if (me == T_RED) {
        for (int r=1; r<DIM-1; r++) {
            if (tb->map[r][0] == me) {
                seen[r][0] = 1;
                queue[q_in++] = (Point){r, 0};
            }
        }
    } else {
        for (int c=1; c<DIM-1; c++) {
            if (tb->map[0][c] == me) {
                seen[0][c] = 1;
                queue[q_in++] = (Point){0, c};
            }
        }
    }

    while (q_out < q_in) {
        Point curr = queue[q_out++];
        if (me == T_RED && curr.c == DIM-1) { tb->game_over = true; tb->winner = me; return true; }
        if (me == T_BLK && curr.r == DIM-1) { tb->game_over = true; tb->winner = me; return true; }

        for (int i=0; i<tb->n_links; i++) {
            Link l = tb->links[i];
            Point next = {-1, -1};

            if (l.u.r == curr.r && l.u.c == curr.c) next = l.v;
            else if (l.v.r == curr.r && l.v.c == curr.c) next = l.u;

            if (next.r != -1 && !seen[next.r][next.c] && tb->map[next.r][next.c] == me) {
                seen[next.r][next.c] = 1;
                queue[q_in++] = next;
            }
        }
    }
    return false;
}

void next_turn(TwixtBoard *tb) {
    tb->turn = (tb->turn == T_RED) ? T_BLK : T_RED;
}