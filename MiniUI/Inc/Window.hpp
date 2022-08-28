
#ifndef __WINDOW_HPP
#define __WINDOW_HPP

#include "Collections.hpp"

class Window : UI {
public:
    signed short Width;
    signed short Height;
    Thickness Padding;
    Color BackgroundColor;

    Window();

    virtual void Show();

    void SetContent(UI &content);

    static void SetDriver(void (*driver)(short x, short y, short width, short height, int *colors));
    static void SetSleepFunc(void (*sleepFunc)(unsigned int ms));
private:
    static void *ScreenDriver;
    static void *SleepFunc;
    UI *Content = (UI *)0;

    virtual void OnDraw(Graphics &g);

    void SetParent(UI &obj, UI &parent);
};

#endif // __WINDOW_H
