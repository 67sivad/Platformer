#include "physics.h"
#include "myLib.h"

void moveVectorX(VectorPoint *point) {
    int a = point->haccel;
    int v = point->hvelocity;
    int x = point->x;
    point->x = x + v;
    point->hvelocity = min(v + a, MAX_RUN_SPEED);
}

void moveVectorY(VectorPoint *point) {
    int a = point->vaccel;
    int v = point->vvelocity;
    int y = point->y;
    if (point->isFalling) {
        a-=GRAVITY;
    }
    point->y = min(y-v, 143);
    if (point->y == 143) {
        point->isFalling = 0;
    }
    point->vvelocity = v + a;
}

void jump(Player *player) {
    player->point.vvelocity = 15;
    player->point.isFalling = 1;
}
