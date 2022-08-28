
#include "Bitmap.hpp"

Bitmap::Bitmap(const Image &img) : Width(img.Width), Height(img.Height), Data((Color *)img.Data) {
    
}

Bitmap::Bitmap(Size &size, Color *buffer) : Width(size.Width), Height(size.Height), Data(buffer) {
    
}

Bitmap::Bitmap(signed short width, signed short height, Color *buffer) : Width(width), Height(height), Data(buffer) {
    
}

Color Bitmap::GetPixel(Point &point) {
    return this->GetPixel(point.X, point.Y);
}

Color Bitmap::GetPixel(signed short x, signed short y) {
    return this->Data[this->Width * y + x];
}

void Bitmap::SetPixel(Point &point, Color &color) {
    this->SetPixel(point.X, point.Y, color);
}

void Bitmap::SetPixel(signed short x, signed short y, Color &color) {
    this->Data[this->Width * y + x] = color;
}
