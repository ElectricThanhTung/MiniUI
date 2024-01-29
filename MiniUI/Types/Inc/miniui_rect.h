
#ifndef __MINIUI_RECT_H
#define __MINIUI_RECT_H

#include "miniui_point.h"
#include "miniui_size.h"

class Rect {
public:
    union {
    public:
        struct {
        public:
            const int16_t Left;
            const int16_t Top;
        };
        const Point Location;
    };
    union {
    public:
        struct {
        public:
            const int16_t Width;
            const int16_t Height;
        };
        const ::Size Size;
    };

    Rect(void);
    Rect(const ::Size &size);
    Rect(const Point &point, const ::Size &size);
    Rect(int16_t width, int16_t height);
    Rect(int16_t left, int16_t top, int16_t width, int16_t height);
    Rect(const Rect &rect);

    void operator=(const Rect &rect);

    bool operator==(const Rect &another) const;
    bool operator!=(const Rect &another) const;
};

#endif /* __MINIUI_RECT_H */
