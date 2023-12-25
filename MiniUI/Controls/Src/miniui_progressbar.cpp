
#include "miniui_progressbar.h"

ProgressBar::ProgressBar(void) : Control(Size(Size::None, 25)), color(Color::Green), backColor(Color::LightGray), borderColor(Color::Gray) {
    this->value = 0;
    this->maxValue = 100;
    this->borderSize = 1;
    this->SetMargin(Thickness(2));
}

ProgressBar::ProgressBar(uint16_t maxValue) : Control(Size(Size::None, 25)), color(Color::Green), backColor(Color::LightGray), borderColor(Color::Gray) {
    this->value = 0;
    this->maxValue = maxValue;
    this->borderSize = 1;
    this->SetMargin(Thickness(2));
}

const char *ProgressBar::GetType(void) {
    return "ProgressBar";
}

void ProgressBar::SetColor(const Color &color) {
    this->color = color;
}

const Color &ProgressBar::GetColor(void) const {
    return this->color;
}

void ProgressBar::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &ProgressBar::GetBackColor(void) const {
    return this->backColor;
}

void ProgressBar::SetBorderColor(const Color &color) {
    this->borderColor = color;
}

const Color &ProgressBar::GetBorderColor(void) const {
    return this->borderColor;
}

void ProgressBar::SetMaxValue(uint16_t maxValue) {
    this->maxValue = maxValue;
}

uint16_t ProgressBar::GetMaxValue(void) {
    return this->maxValue;
}

void ProgressBar::SetValue(uint16_t value) {
    this->value = value;
}

uint16_t ProgressBar::GetValue(void) {
    return this->value;
}

void ProgressBar::SetBorderSize(const uint8_t value) {
    this->borderSize = value;
}

uint8_t ProgressBar::GetBorderSize(void) const {
    return this->borderSize;
}

void ProgressBar::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    if(width >= 0)
        this->SetActualWidth(width);
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        width = MiniUI_MAX(referWidth - margin.Left - margin.Right, 0);
        this->SetActualWidth(width);
    }
    else
        this->SetActualWidth(0);
}

void ProgressBar::UpdateActualHeight(int16_t referHeight) {
    int16_t height = this->GetSize().Height;
    if(height >= 0)
        this->SetActualHeight(height);
    else if((height == Size::None) && (referHeight >= 0)) {
        const Thickness &margin = this->GetMargin();
        height = MiniUI_MAX(referHeight - margin.Top - margin.Bottom, 0);
        this->SetActualHeight(height);
    }
    else
        this->SetActualHeight(0);
}

void ProgressBar::OnDraw(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    if((this->borderColor.A != 0x00) && (this->borderSize > 0))
        g.DrawRectangle(Pen(this->borderColor, this->borderSize), actualSize);
    if(this->backColor.A != 0x00) {
        int16_t width = actualSize.Width - this->borderSize * 2;
        int16_t height = actualSize.Height - this->borderSize * 2;
        g.FillRectangle(this->backColor, Rect(this->borderSize, this->borderSize, width, height));
    }
    if(this->value > 0) {
        int16_t height = MiniUI_MAX(actualSize.Height - this->borderSize * 2, 0);
        int16_t width = MiniUI_MAX(actualSize.Width - this->borderSize * 2, 0);
        width = width * this->value / this->maxValue;
        g.FillRectangle(this->color, Rect(this->borderSize, this->borderSize, width, height));
    }
}
