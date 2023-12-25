
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
    uint8_t visible : 1;
    uint8_t verticalAlignment : 2;
    uint8_t horizontalAlignment : 2;

    Control(const Control &) = delete;
    void operator=(const Control &) = delete;
protected:
    Control(const Size &size);
public:
    virtual void RequestUpdate(void);
    virtual void OnDraw(Graphics &g) = 0;
    virtual void UpdateActualWidth(int16_t referWidth) = 0;
    virtual void UpdateActualHeight(int16_t referHeight) = 0;

    virtual const char *GetType(void);

    bool operator==(Control &another);
    bool operator!=(Control &another);

    void SetParentList(void *parentList);
    void *GetParentList(void) const;

    void SetPrev(Control &prev);
    Control &GetPrev(void) const;

    void SetNext(Control &next);
    Control &GetNext(void) const;

    void SetParent(Control &parent);
    Control &GetParent(void) const;

    void SetActualWidth(int16_t value);
    void SetActualHeight(int16_t value);
    const Size &GetActualSize(void) const;

    void SetSize(const Size &size);
    void SetSize(int16_t width, int16_t height);
    void SetWidth(int16_t width);
    void SetHeight(int16_t height);
    const Size &GetSize(void) const;

    void SetMargin(const Thickness &margin);
    void SetMargin(int16_t uniformSize);
    void SetMargin(int16_t left, int16_t top, int16_t right, int16_t bottom);
    void SetMarginLeft(int16_t left);
    void SetMarginTop(int16_t top);
    void SetMarginRight(int16_t right);
    void SetMarginBottom(int16_t bottom);
    const Thickness &GetMargin(void) const;

    void SetVisible(bool visible);
    bool GetVisible(void) const;

    void SetVerticalAlignment(const VerticalAlignment &alignment);
    VerticalAlignment GetVerticalAlignment(void) const;

    void SetHorizontalAlignment(const HorizontalAlignment &alignment);
    HorizontalAlignment GetHorizontalAlignment(void) const;

    ~Control(void);
};

#define NULL_CONTROL            (*(Control *)0)

#endif /* __MINIUI_CONTROL_H */
