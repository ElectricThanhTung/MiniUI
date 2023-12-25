
#ifndef __MINIUI_CONTROL_H
#define __MINIUI_CONTROL_H

#include "miniui_graphics.h"

class Control {
private:
    void *parentList;
    Control *prev;
    Control *next;
    Control *parent;
    Size actualSize;
    Size size;
    Thickness margin;
    bool visible;

    Control(const Control &) = delete;
    void operator=(const Control &) = delete;
protected:
    Control(const Size &size);
public:
    virtual void RequestUpdate(void);
    virtual void OnDraw(Graphics &g) = 0;
    virtual void UpdateActualWidth(int16_t referWidth) = 0;
    virtual void UpdateActualHeight(int16_t referHeight) = 0;

    bool operator==(Control &another);
    bool operator!=(Control &another);

    void SetParentList(void *parentList);
    void *GetParentList(void);

    void SetPrev(Control &prev);
    Control &GetPrev(void);

    void SetNext(Control &next);
    Control &GetNext(void);

    void SetParent(Control &parent);
    Control &GetParent(void);

    void SetActualWidth(int16_t value);
    void SetActualHeight(int16_t value);
    const Size &GetActualSize(void);

    void SetSize(const Size &size);
    const Size &GetSize(void);

    void SetMargin(const Thickness &margin);
    const Thickness &GetMargin(void);

    void SetVisible(bool visible);
    bool GetVisible(void);

    ~Control(void);
};

#define NULL_CONTROL            (*(Control *)0)

#endif /* __MINIUI_CONTROL_H */
