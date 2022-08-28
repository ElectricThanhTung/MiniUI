
#ifndef __RECTANGLE_HPP
#define __RECTANGLE_HPP

#include "Size.hpp"
#include "Point.hpp"

class Rect {
public:
    signed short Left;
    signed short Top;
    unsigned short Width;
    unsigned short Height;

    Rect(Size &size);
    Rect(Point &point, Size &size);
    Rect(unsigned short width, unsigned short height);
    Rect(signed short left, signed short top, unsigned short width, unsigned short height);
};

#endif // __RECTANGLE_HPP
