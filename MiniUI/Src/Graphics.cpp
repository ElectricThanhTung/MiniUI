
#include "Graphics.hpp"

Graphics::Graphics(Bitmap &bitmap) : BitmapBuffer(bitmap), Left(0), Top(0), Right(bitmap.Width - 1), Bottom(bitmap.Height - 1) {

}

Graphics::Graphics(Bitmap &bitmap, signed short left, signed short top, signed short right, signed short bottom) :
BitmapBuffer(bitmap), Left(left), Top(top), Right(right), Bottom(bottom) {

}

void Graphics::Clear() {
    this->Clear(Color::Transparent);
}

void Graphics::Clear(const Color &color) {
    signed short w = this->Right - this->Left + 1;
    signed short h = this->Bottom - this->Top + 1;
    for(signed short x = 0; x < w; x++) {
        for(signed short y = 0; y < h; y++)
            this->BitmapBuffer.Data[x + y * this->BitmapBuffer.Width] = color;
    }
}

void Graphics::DrawLine(const Pen &pen, const Point &point1, const Point &point2) {
    // TODO
}

void Graphics::DrawRectangle(const Color &color, const Rect &rect) {
    // TODO
}

void Graphics::FullRectangle(const Color &color, const Rect &rect) {
    signed short x1 = rect.Left - this->Left;
    signed short y1 = rect.Top - this->Top;
    signed short x2 = (rect.Width + rect.Left) - this->Left;
    signed short y2 = (rect.Height + rect.Top) - this->Top;
    if(x1 < 0)
        x1 = 0;
    if(y1 < 0)
        y1 = 0;
    if(x2 > this->Right - this->Left)
        x2 = this->Right - this->Left;
    if(y2 > (this->Bottom - this->Top))
        y2 = this->Bottom - this->Top;
    if(y1 > y2)
        return;
    for(signed short x = x1; x <= x2; x++) {
        for(signed short y = y1; y <= y2; y++)
            this->BitmapBuffer.Data[x + y * this->BitmapBuffer.Width] = color;
    }
}
