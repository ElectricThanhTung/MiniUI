
#ifndef __MINIUI_COMMON_H
#define __MINIUI_COMMON_H

#include <stdint.h>

#define MiniUI_ABS(value)                  (((value) < 0) ? -(value) : (value))

int16_t MiniUI_MIN(int16_t a, int16_t b);
int16_t MiniUI_MIN(int16_t a, int16_t b, int16_t c);
int16_t MiniUI_MIN(int16_t a, int16_t b, int16_t c, int16_t d);

int16_t MiniUI_MAX(int16_t a, int16_t b);
int16_t MiniUI_MAX(int16_t a, int16_t b, int16_t c);
int16_t MiniUI_MAX(int16_t a, int16_t b, int16_t c, int16_t d);

uint32_t MiniUI_StrLen(const char *str);

#endif /* __MINIUI_COMMON_H */
