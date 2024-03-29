
#ifndef __MINIUI_STACKPANEL_H
#define __MINIUI_STACKPANEL_H

#include "miniui_control.h"
#include "miniui_collections.h"

class StackPanel : public Control {
private:
    Orientation orientation;
    Color backColor;

    StackPanel(const StackPanel &) = delete;
    void operator=(const StackPanel &) = delete;

    void SetParentList(void *) = delete;
    void *GetParentList(void) = delete;
    void SetPrev(Control &) = delete;
    Control &GetPrev(void) = delete;
    void SetNext(Control &) = delete;
    Control &GetNext(void) = delete;
    void SetParent(Control &) = delete;

    void DrawHorizontal(Graphics &g);
    void DrawVertical(Graphics &g);
    void DrawNone(Graphics &g);
protected:
    virtual void OnDraw(Graphics &g);
    virtual void UpdateActualWidth(int16_t referWidth);
    virtual void UpdateActualHeight(int16_t referHeight);

    using Control::SetActualWidth;
    using Control::SetActualHeight;
public:
    Collections Children;

    StackPanel(void);

    virtual const char *GetType(void);

    void SetOrientation(const Orientation &value);
    const Orientation &GetOrientation(void) const;

    void SetBackColor(const Color &color);
    const Color &GetBackColor(void) const;
};

#endif /* __MINIUI_STACKPANEL_H */
