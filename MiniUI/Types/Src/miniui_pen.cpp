
#include <string.h>
#include "miniui_pen.h"

Pen::Pen(void) : Width(1), Color(Color::Black) {

}

Pen::Pen(const ::Color &color, uint16_t width) : Width(width), Color(color) {

}

Pen::Pen(const Pen &pen) : Width(pen.Width), Color(pen.Color) {

}

void Pen::operator=(const Pen &pen) {
    memcpy((void *)this, &pen, sizeof(*this));
}
