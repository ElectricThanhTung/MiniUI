
#ifndef __MINIUI_USER_CONTROL_H
#define __MINIUI_USER_CONTROL_H

#include "miniui_control.h"

class UserControl : public Control {
private:
    Control *content;
    Color backColor;

    UserControl(UserControl &) = delete;
    void operator=(const UserControl &) = delete;

    void SetParentList(void *) = delete;
    void *GetParentList(void) = delete;
    void SetPrev(Control &) = delete;
    Control &GetPrev(void) = delete;
    void SetNext(Control &) = delete;
    Control &GetNext(void) = delete;
    void SetParent(Control &) = delete;
protected:
    UserControl(void);

    virtual void OnDraw(Graphics &g);
    virtual void UpdateActualWidth(int16_t referWidth);
    virtual void UpdateActualHeight(int16_t referHeight);

    using Control::SetActualWidth;
    using Control::SetActualHeight;
public:
    void SetContent(Control &control);
    Control &GetContent(void);

    void SetBackColor(const Color &color);
    const Color &GetBackColor(void);
};

#endif /* __MINIUI_USER_CONTROL_H */
