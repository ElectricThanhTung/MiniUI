
#ifndef __MINIUI_LINE_H
#define __MINIUI_LINE_H

#include "miniui_point.h"

class Line {
public:
    union {
    public:
        struct {
        public:
            const int16_t X1;
            const int16_t Y1;
        };
        const Point Point1;
    };
    union {
    public:
        struct {
        public:
            const int16_t X2;
            const int16_t Y2;
        };
        const Point Point2;
    };

    Line(void);
    Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    Line(const Point &point1, const Point &point2);
    Line(const Line &line);

    void operator=(const Line &line);
};

#endif /* __MINIUI_LINE_H */
