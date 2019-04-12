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
        a-=10;
    }
    point->y = min(y-v, 143);
    point->vvelocity = v + a;
}
