
#include "miniui_common.h"

int16_t MIN(int16_t a, int16_t b) {
    return (a < b) ? a : b;
}

int16_t MIN(int16_t a, int16_t b, int16_t c) {
    int16_t min = (a < b) ? a : b;
    return (min < c) ? min : c;
}

int16_t MIN(int16_t a, int16_t b, int16_t c, int16_t d) {
    int16_t min = (a < b) ? a : b;
    min = (min < c) ? min : c;
    return (min < d) ? min : d;
}

int16_t MAX(int16_t a, int16_t b) {
    return (a > b) ? a : b;
}

int16_t MAX(int16_t a, int16_t b, int16_t c) {
    int16_t max = (a > b) ? a : b;
    return (max > c) ? max : c;
}

int16_t MAX(int16_t a, int16_t b, int16_t c, int16_t d) {
    int16_t max = (a > b) ? a : b;
    max = (max > c) ? max : c;
    return (max > d) ? max : d;
}
