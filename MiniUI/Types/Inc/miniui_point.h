
#ifndef __MINIUI_POINT_H
#define __MINIUI_POINT_H

#include <stdint.h>

class Point {
public:
    const int16_t X;
    const int16_t Y;

    Point(void);
    Point(int16_t x, int16_t y);
    Point(const Point &point);

    void operator=(const Point &point);
};

#endif /* __MINIUI_POINT_H */
