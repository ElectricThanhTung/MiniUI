
#ifndef __MINIUI_PROGRESSBAR_H
#define __MINIUI_PROGRESSBAR_H

#include "miniui_control.h"

class ProgressBar : public Control {
private:
    Color color;
    Color backColor;
    Color borderColor;
    uint16_t value;
    uint16_t maxValue;
    uint8_t borderSize;

    ProgressBar(const ProgressBar &) = delete;
    void operator=(const ProgressBar &) = delete;

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
    ProgressBar(void);
    ProgressBar(uint16_t maxValue);

    virtual const char *GetType(void);

    void SetColor(const Color &color);
    const Color &GetColor(void) const;

    void SetBackColor(const Color &color);
    const Color &GetBackColor(void) const;

    void SetBorderColor(const Color &color);
    const Color &GetBorderColor(void) const;

    void SetBorderSize(const uint8_t value);
    uint8_t GetBorderSize(void) const;

    void SetMaxValue(uint16_t maxValue);
    uint16_t GetMaxValue(void);

    void SetValue(uint16_t value);
    uint16_t GetValue(void);
};

#endif /* __MINIUI_PROGRESSBAR_H */