
#ifndef __MINIUI_PEN_H
#define __MINIUI_PEN_H

#include <stdint.h>
#include "miniui_color.h"

class Pen {
public:
    const uint16_t Width;
    const ::Color Color;

    Pen(void);
    Pen(const ::Color &color, uint16_t width = 1);
    Pen(const Pen &pen);

    void operator=(const Pen &pen);
};

#endif /* __MINIUI_PEN_H */
