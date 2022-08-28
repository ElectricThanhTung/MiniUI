
#include "UI.hpp"

UI::UI() : Parent(0), Margin(0, 0, 0, 0), ActualWidth(-1), ActualHeight(-1) {
    this->Width = -1;
    this->Height = -1;
}

void UI::Draw(Graphics &g, Point &point) {
    this->Draw(g, point.X, point.Y);
}

void UI::Draw(Graphics &g, Point &point, Size &size) {
    this->Draw(g, point.X, point.Y, size.Width, size.Height);
}

void UI::Draw(Graphics &g, Rect &rect) {
    this->Draw(g, rect.Left, rect.Top, rect.Width, rect.Height);
}

void UI::Draw(Graphics &g, signed short x, signed short y) {
    if(x == g.Left && y == g.Top)
        this->OnDraw(g);
    else {
        Graphics temp = Graphics(g.BitmapBuffer, g.Left - x, g.Top - y, g.Right - x, g.Bottom - y);
        this->OnDraw(temp);
    }
}

void UI::Draw(Graphics &g, signed short x, signed short y, signed short width, signed short height) {
    signed short x1 = g.Left - x;
    signed short y1 = g.Top - y;
    signed short x2 = g.Right - x;
    signed short y2 = g.Bottom - y;
    if(x1 > g.Left)
        x1 = g.Left;
    if(y1 > g.Top)
        y1 = g.Top;
    if((width + x - 1) < x2)
        x2 = width + x - 1;
    if((height + y - 1) < y2)
        y2 = height + y - 1;
    if(x2 < x1 || y2 < y1)
        return;
    Graphics temp = Graphics(g.BitmapBuffer, x1, y1, x2, y2);
    this->OnDraw(temp);
}
