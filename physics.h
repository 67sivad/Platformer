typedef struct {
    int hvelocity;
    int vvelocity;
    int isFalling;
    int haccel;
    int vaccel;
    int x;
    int y;
} VectorPoint;

#define GRAVITY 10

#define MAX_RUN_SPEED 10

void moveVectorY(VectorPoint *point);
void moveVectorX(VectorPoint *point);
