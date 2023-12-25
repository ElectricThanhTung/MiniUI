
#ifndef __MINIUI_COMMON_H
#define __MINIUI_COMMON_H

#include <stdint.h>

#define ABS(value)                  (((value) < 0) ? -(value) : (value))

int16_t MIN(int16_t a, int16_t b);
int16_t MIN(int16_t a, int16_t b, int16_t c);
int16_t MIN(int16_t a, int16_t b, int16_t c, int16_t d);

int16_t MAX(int16_t a, int16_t b);
int16_t MAX(int16_t a, int16_t b, int16_t c);
int16_t MAX(int16_t a, int16_t b, int16_t c, int16_t d);

#endif /* __MINIUI_COMMON_H */
