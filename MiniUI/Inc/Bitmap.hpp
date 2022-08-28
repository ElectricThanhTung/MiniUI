
#ifndef __BITMAP_HPP
#define __BITMAP_HPP

#include "Color.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include "Image.hpp"

class Bitmap {
public:
    const signed short Width;
    const signed short Height;
    Color *const Data;

    Bitmap(const Image &img);
    Bitmap(Size &size, Color *buffer);
    Bitmap(signed short width, signed short height, Color *buffer);

    Color GetPixel(Point &point);
    Color GetPixel(signed short x, signed short y);

    void SetPixel(Point &point, Color &color);
    void SetPixel(signed short x, signed short y, Color &color);
};

#endif // __BITMAP_HPP
