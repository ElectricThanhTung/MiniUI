
#include "miniui_bitmap.h"

const Color &Bitmap::GetPixel(const Point &point) const {
    return this->Data[point.Y * this->Width + point.X];
}

const Color &Bitmap::GetPixel(int16_t x, int16_t y) const {
    return this->Data[y * this->Width + x];
}

void Bitmap::SetPixel(const Point &point, const Color &color) {
    this->Data[point.Y * this->Width + point.X] = color;
}

void Bitmap::SetPixel(int16_t x, int16_t y, const Color &color) {
    this->Data[y * this->Width + x] = color;
}
