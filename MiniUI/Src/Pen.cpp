
#include "Pen.hpp"

Pen::Pen(Color &color) : color(color) {
    this->Width = 1;
}

Pen::Pen(unsigned short width, Color &color) : color(color) {
    this->Width = width;
}
