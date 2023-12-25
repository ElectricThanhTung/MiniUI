
#ifndef __MINIUI_WINDOW_H
#define __MINIUI_WINDOW_H

#include "miniui_control.h"

#define MINIUI_WINDOWS_W                    640
#define MINIUI_WINDOWS_H                    512

#define MINIUI_GRAPHIC_W                    128
#define MINIUI_GRAPHIC_H                    128

class Window : public Control {
private:
    Control *content;
    Window(const Window &) = delete;
    void operator=(const Window &) = delete;

    void SetParentList(void *) = delete;
    void *GetParentList(void) = delete;
    void SetPrev(Control &) = delete;
    Control &GetPrev(void) = delete;
    void SetNext(Control &) = delete;
    Control &GetNext(void) = delete;
    void SetParent(Control &) = delete;
    void SetSize(const Size &) = delete;
    const Size &GetSize(void) = delete;
protected:
    virtual void OnDraw(Graphics &g);
    virtual void UpdateActualWidth(int16_t referWidth);
    virtual void UpdateActualHeight(int16_t referHeight);

    using Control::SetActualWidth;
    using Control::SetActualHeight;
public:
    static void (*ScreenDriver)(const RgbColor *rgbBuff, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    Window(void);
    Window(const Window &&window);

    void SetContent(Control &control);
    Control &GetContent(void);

    void Update(void);
};

#endif /* __MINIUI_WINDOW_H */
