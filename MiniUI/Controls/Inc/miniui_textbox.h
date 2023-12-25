
#ifndef __MINIUI_TEXTBOX_H
#define __MINIUI_TEXTBOX_H

#include "miniui_control.h"

class TextBox : public Control {
private:
    const char *text;
    Thickness padding;
    Color backColor;
    Color foreColor;
    Color borderColor;
    Font font;
    uint8_t borderSize;
    uint8_t passwordChar;

    TextBox(const TextBox &) = delete;
    void operator=(const TextBox &) = delete;

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
    TextBox(void);

    virtual const char *GetType(void);

    void SetText(const char *text);
    const char *GetText(void) const;

    void SetBackColor(const Color &color);
    const Color &GetBackColor(void) const;

    void SetForeColor(const Color &color);
    const Color &GetForeColor(void) const;

    void SetFont(const Font &font);
    const Font &GetFont(void) const;

    void SetBorderColor(const Color &color);
    const Color &GetBorderColor(void) const;

    void SetBorderSize(const uint8_t value);
    uint8_t GetBorderSize(void) const;

    void SetPasswordChar(const char value);
    const char GetPasswordChar(void) const;
};

#endif /* __MINIUI_TEXTBOX_H */
