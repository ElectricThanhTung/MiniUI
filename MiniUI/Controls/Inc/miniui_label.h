
#ifndef __MINIUI_LABEL_H
#define __MINIUI_LABEL_H

#include "miniui_control.h"

class Label : public Control {
private:
    const char *text;
    Color foreColor;
    Font font;

    Label(const Label &) = delete;
    void operator=(const Label &) = delete;

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
    Label(void);
    Label(const char *text);
    Label(const char *text, const Color &foreColor);
    Label(const char *text, const Color &foreColor, const ::Font &font);

    virtual const char *GetType(void);

    void SetText(const char *text);
    const char *GetText(void) const;

    void SetForeColor(const Color &color);
    const Color &GetForeColor(void) const;

    void SetFont(const Font &font);
    const Font &GetFont(void) const;
};

#endif /* __MINIUI_LABEL_H */
