
#ifndef __GRAPHICS_HPP
#define __GRAPHICS_HPP

#include "Pen.hpp"
#include "Size.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "Bitmap.hpp"
#include "Thickness.hpp"

class Graphics {
public:
    Bitmap &BitmapBuffer;
    const signed short Left;
    const signed short Top;
    const signed short Right;
    const signed short Bottom;

    Graphics(Bitmap &bitmap);
    Graphics(Bitmap &bitmap, signed short left, signed short top, signed short width, signed short height);

    void Clear();
    void Clear(const Color &color);

    void DrawLine(const Pen &pen, const Point &point1, const Point &point2);
    void DrawRectangle(const Color &color, const Rect &rect);
    void FullRectangle(const Color &color, const Rect &rect);
};

#endif // __GRAPHICS_HPP
