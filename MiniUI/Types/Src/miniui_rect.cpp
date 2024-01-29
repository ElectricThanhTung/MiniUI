#include <string.h>
#include "miniui_rect.h"

Rect::Rect(void) : Location(0, 0), Size(0, 0) {

}

Rect::Rect(const ::Size &size) : Location(0, 0), Size(size) {

}

Rect::Rect(const Point &point, const ::Size &size) : Location(point), Size(size) {

}

Rect::Rect(int16_t width, int16_t height) : Location(0, 0), Size(width, height) {

}

Rect::Rect(int16_t left, int16_t top, int16_t width, int16_t height) : Location(left, top), Size(width, height) {

}

Rect::Rect(const Rect &rect) : Location(rect.Location), Size(rect.Size) {

}

void Rect::operator=(const Rect &rect) {
    memcpy((void *)this, &rect, sizeof(*this));
}

bool Rect::operator==(const Rect &another) const {
    return (this->Left == another.Left) && (this->Top == another.Top) && (this->Width == another.Width) && (this->Height == another.Height);
}

bool Rect::operator!=(const Rect &another) const {
    return (this->Left != another.Left) || (this->Top != another.Top) || (this->Width != another.Width) || (this->Height != another.Height);
}
