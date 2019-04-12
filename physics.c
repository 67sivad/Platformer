#include "physics.h"
#include "myLib.h"

void moveVectorX(VectorPoint *point) {
    int a = point->haccel;
    int v = point->hvelocity;
    int x = point->x;
    point->x = x + v;
    point->hvelocity = v + a;
}

void moveVectorY(VectorPoint *point) {
    int a = point->vaccel;
    int v = point->vvelocity;
    int y = point->y;
    if (point->isFalling) {
        a-=10;
    }
    point->y = max(y+v, 0);
    point->vvelocity = v + a;
}
