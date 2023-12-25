
#ifndef __MINIUI_WINDOW_H
#define __MINIUI_WINDOW_H

#if __has_include("miniui_conf.h")
    #include "miniui_conf.h"
#endif

#include "miniui_control.h"

#ifndef MINIUI_WINDOWS_W
    #define MINIUI_WINDOWS_W                    512
    #warning "MINIUI_WINDOWS_W is not defined. Default value will be used"
#endif /* MINIUI_WINDOWS_W */

#ifndef MINIUI_WINDOWS_H
    #define MINIUI_WINDOWS_H                    512
    #warning "MINIUI_WINDOWS_H is not defined. Default value will be used"
#endif /* MINIUI_WINDOWS_H */

#ifndef MINIUI_GRAPHIC_W
    #define MINIUI_GRAPHIC_W                    128
    #warning "MINIUI_GRAPHIC_W is not defined. Default value will be used"
#endif /* MINIUI_GRAPHIC_W */

#ifndef MINIUI_GRAPHIC_H
    #define MINIUI_GRAPHIC_H                    128
    #warning "MINIUI_GRAPHIC_H is not defined. Default value will be used"
#endif /* MINIUI_GRAPHIC_H */

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
    void SetWidth(int16_t width) = delete;
    void SetHeight(int16_t height) = delete;
    const Size &GetSize(void) = delete;
    void SetMargin(const Thickness &margin) = delete;
    void SetMargin(int16_t uniformSize) = delete;
    void SetMargin(int16_t left, int16_t top, int16_t right, int16_t bottom) = delete;
    void SetMarginLeft(int16_t left) = delete;
    void SetMarginTop(int16_t top) = delete;
    void SetMarginRight(int16_t right) = delete;
    void SetMarginBottom(int16_t bottom) = delete;
    const Thickness &GetMargin(void) = delete;
    void SetVisible(bool visible) = delete;
    bool GetVisible(void) = delete;
    void SetVerticalAlignment(const VerticalAlignment &alignment) = delete;
    VerticalAlignment GetVerticalAlignment(void) = delete;
    void SetHorizontalAlignment(const HorizontalAlignment &alignment) = delete;
    HorizontalAlignment GetHorizontalAlignment(void) = delete;
protected:
    virtual void OnDraw(Graphics &g);
    virtual void UpdateActualWidth(int16_t referWidth);
    virtual void UpdateActualHeight(int16_t referHeight);

    using Control::SetActualWidth;
    using Control::SetActualHeight;
public:
    static void (*ScreenDriver)(const RgbColor *rgbBuff, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    Window(void);

    virtual const char *GetType(void);

    void SetContent(Control &control);
    Control &GetContent(void) const;

    void UpdateActualSize(void);
    void Update(void);
};

#endif /* __MINIUI_WINDOW_H */
