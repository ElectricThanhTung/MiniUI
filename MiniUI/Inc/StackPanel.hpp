
#ifndef __STACKPANEL_HPP
#define __STACKPANEL_HPP

#include "Collections.hpp"

typedef enum {
    Horizontal = 0,
    Vertical = 1,
} Orientation_TypeDef;

class StackPanel : public UI {
public:
    Thickness Padding;
    Orientation_TypeDef Orientation;
    Color BackgroundColor;
    Collections Content;

    StackPanel();
private:
    virtual void OnDraw(Graphics &g);

    void DrawHorizontal(Graphics &g);
    void DrawVertical(Graphics &g);
};

#endif // __STACKPANEL_HPP
