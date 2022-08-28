
#ifndef __PEN_HPP
#define __PEN_HPP

#include "Color.hpp"

class Pen {
public:
    unsigned short Width;
    Color color;

    Pen(Color &color);
    Pen(unsigned short width, Color &color);
};

#endif // __PEN_HPP
