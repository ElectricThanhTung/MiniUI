
#ifndef __CONTROL_HPP
#define __CONTROL_HPP

#include "Graphics.hpp"

class UI {
public:
    UI();
    signed short Width;
    signed short Height;
    const signed short ActualWidth;
    const signed short ActualHeight;
    Thickness Margin;
    UI *const Parent;

    void Draw(Graphics &g, Point &point);
    void Draw(Graphics &g, Point &point, Size &size);
    void Draw(Graphics &g, Rect &rect);
    void Draw(Graphics &g, signed short x, signed short y);
    void Draw(Graphics &g, signed short x, signed short y, signed short width, signed short height);
private:
    virtual void OnDraw(Graphics &g) = 0;
};

#endif // __CONTROL_HPP
