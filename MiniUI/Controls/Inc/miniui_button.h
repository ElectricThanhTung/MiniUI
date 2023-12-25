
#ifndef __MINIUI_BUTTON_H
#define __MINIUI_BUTTON_H

#include "miniui_control.h"

class Button : public Control {
private:
    Control *content;
    const char *text;
    Color backColor;
    Color borderColor;
    Color foreColor;
    Font font;
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

    using Control::SetActualWidth;
    using Control::SetActualHeight;
public:
    Button(void);
    Button(Control &content);
    Button(const char *text);
    Button(const char *text, const Color &foreColor);
    Button(const char *text, const Color &foreColor, const ::Font &font);

    virtual const char *GetType(void);

    void SetContent(const char *text);
    void SetContent(Control &control);
    void *GetContent(void) const;

    void SetForeColor(const Color &color);
    const Color &GetForeColor(void) const;

    void SetFont(const Font &font);
    const Font &GetFont(void) const;

    void SetBackColor(const Color &color);
    const Color &GetBackColor(void) const;

    void SetBorderColor(const Color &color);
    const Color &GetBorderColor(void) const;

    void SetBorderSize(const uint8_t value);
    uint8_t GetBorderSize(void) const;
};

#endif /* __MINIUI_BUTTON_H */
