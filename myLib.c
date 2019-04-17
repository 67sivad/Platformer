#include "myLib.h"

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int abs(int a) {
    if (a > 0) {
        return a;
    } else {
        return -a;
    }
}
