
#include "miniui_common.h"
#include "miniui_font.h"

int16_t MiniUI_MIN(int16_t a, int16_t b) {
    return (a < b) ? a : b;
}

int16_t MiniUI_MIN(int16_t a, int16_t b, int16_t c) {
    int16_t min = (a < b) ? a : b;
    return (min < c) ? min : c;
}

int16_t MiniUI_MIN(int16_t a, int16_t b, int16_t c, int16_t d) {
    int16_t min = (a < b) ? a : b;
    min = (min < c) ? min : c;
    return (min < d) ? min : d;
}

int16_t MiniUI_MAX(int16_t a, int16_t b) {
    return (a > b) ? a : b;
}

int16_t MiniUI_MAX(int16_t a, int16_t b, int16_t c) {
    int16_t max = (a > b) ? a : b;
    return (max > c) ? max : c;
}

int16_t MiniUI_MAX(int16_t a, int16_t b, int16_t c, int16_t d) {
    int16_t max = (a > b) ? a : b;
    max = (max > c) ? max : c;
    return (max > d) ? max : d;
}

uint32_t MiniUI_StrLen(const char *str) {
    uint32_t length = 0;
    while(*str) {
        length++;
        str += Font::Utf8ByteCount(*str);
    }
    return length;
}
