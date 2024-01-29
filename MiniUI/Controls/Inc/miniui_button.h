
#ifndef __MINIUI_BUTTON_H
#define __MINIUI_BUTTON_H

#include "miniui_control.h"

class Button : public Control {
private:
    Control *content;
    Color backColor;
    Color borderColor;
    uint8_t borderSize;

    Button(const Button &) = delete;
    void operator=(const Button &) = delete;

    void SetParentList(void *) = delete;
    void *GetParentList(void) = delete;
    void SetPrev(Control &) = delete;
    Control &GetPrev(void) = delete;
    void SetNext(Control &) = delete;
    Control &GetNext(void) = delete;
    void SetParent(Control &) = delete;
protected:
    virtual void OnDraw(Graphics &g);
    virtual void UpdateActualWidth(int16_t referWidth);
    virtual void UpdateActualHeight(int16_t referHeight);
    virtual void UpdateLocation(void);

    using Control::SetActualWidth;
    using Control::SetActualHeight;
    using Control::SetLocation;
public:
    Button(void);
    Button(Control &content);

    void SetContent(Control &control);
    Control &GetContent(void);

    void SetBackColor(const Color &color);
    const Color &GetBackColor(void);

    void SetBorderColor(const Color &color);
    const Color &GetBorderColor(void);

    void SetBorderSize(const uint8_t value);
    uint8_t GetBorderSize(void);
};

#endif /* __MINIUI_BUTTON_H */
