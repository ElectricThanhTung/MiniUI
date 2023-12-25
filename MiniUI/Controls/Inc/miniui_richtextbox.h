
#ifndef __MINIUI_RICHTEXTBOX_H
#define __MINIUI_RICHTEXTBOX_H

#include "miniui_control.h"

class RichTextBox : public Control {
private:
    const char *text;
    Thickness padding;
    Color backColor;
    Color foreColor;
    Color borderColor;
    Font font;
    uint8_t borderSize;
    uint16_t lineCount;

    RichTextBox(const RichTextBox &) = delete;
    void operator=(const RichTextBox &) = delete;

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
    RichTextBox(void);

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
};

#endif /* __MINIUI_RICHTEXTBOX_H */
