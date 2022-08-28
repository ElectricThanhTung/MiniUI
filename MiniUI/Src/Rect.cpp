
#include "Rect.hpp"

Rect::Rect(Size &size) {
    Rect(0, 0, size.Width, size.Height);
}

Rect::Rect(Point &point, Size &size) {
    Rect(point.X, point.Y, size.Width, size.Height);
}

Rect::Rect(unsigned short width, unsigned short height) {
    Rect(0, 0, width, height);
}

Rect::Rect(signed short left, signed short top, unsigned short width, unsigned short height) {
    this->Left = left;
    this->Top = top;
    this->Width = width;
    this->Height = height;
}
