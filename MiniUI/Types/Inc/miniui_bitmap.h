
#ifndef __MINIUI_BITMAP_H
#define __MINIUI_BITMAP_H

#include "miniui_size.h"
#include "miniui_point.h"
#include "miniui_color.h"

class Bitmap {
public:
    union {
    public:
        struct {
        public:
            const int16_t Width;
            const int16_t Height;
        };
        const ::Size Size;
    };
private:
    Color Data[];
    Bitmap(void) = delete;
    Bitmap(Bitmap &) = delete;
public:
    const Color &GetPixel(const Point &point) const;
    const Color &GetPixel(int16_t x, int16_t y) const;
    void SetPixel(const Point &point, const Color &color);
    void SetPixel(int16_t x, int16_t y, const Color &color);
};

#endif /* __MINIUI_BITMAP_H */
