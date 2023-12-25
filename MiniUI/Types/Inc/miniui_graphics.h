
#ifndef __MINIUI_GRAPHICS_H
#define __MINIUI_GRAPHICS_H

#include <stdint.h>
#include "miniui_common.h"
#include "miniui_point.h"
#include "miniui_size.h"
#include "miniui_line.h"
#include "miniui_rect.h"
#include "miniui_color.h"
#include "miniui_pen.h"
#include "miniui_font.h"
#include "miniui_thickness.h"
#include "miniui_alignment.h"
#include "miniui_orientation.h"

class Graphics {
private:
    const uint16_t dataWidth;
    const int16_t left;
    const int16_t top;
    const int16_t width;
    const int16_t height;
    const int16_t x;
    const int16_t y;
    const int16_t drawableX;
    const int16_t drawableY;
    RgbColor * const data;

    Graphics(const Rect &rect, RgbColor *buffer, uint16_t dataWidth, const Point &origin, const Point &drawable);

    void operator=(const Graphics &g) = delete;

    void DrawChar(const CharInfo &c, const Color &color, const Rect &rect);
public:
    Graphics(const Size &size, RgbColor *buffer);
    Graphics(int16_t width, int16_t height, RgbColor *buffer);
    Graphics(const Rect &rect, RgbColor *buffer);
    Graphics(const Graphics &g);

    Graphics SubGraphics(const Rect &area);
    Graphics SubGraphics(int16_t x, int16_t y);
    Graphics SubGraphics(int16_t x1, int16_t y1, uint16_t x2, uint16_t y2);

    void Clear(void);

    void DrawPixel(const Point &point, const Color &color);
    void DrawLine(const Pen &pen, const Line &line);
    void DrawRectangle(const Pen &pen, const Rect &rect);
    void FillRectangle(const Color &color, const Rect &rect);
    void DrawString(const char *text, const Font &font, const Color &color, const Rect &rect);
    void DrawString(const char *text, uint32_t length, const Font &font, const Color &color, const Rect &rect);
};

#endif /* __MINIUI_GRAPHICS_H */
