
#include "miniui_button.h"
#include "miniui_collections.h"

Button::Button(void) : Control(Size::AutoSize), backColor(Color::LightGray), borderColor(Color::Gray) {
    this->content = 0;
    this->borderSize = 1;
}

Button::Button(Control &content) : Control(Size::AutoSize), backColor(Color::LightGray), borderColor(Color::Gray) {
    this->content = &content;
    this->borderSize = 1;
}

void Button::SetContent(Control &control) {
    Collections *objParentList = (Collections *)control.GetParentList();
    control.SetParent(*this);
    if(objParentList)
        objParentList->Remove(control);
    if(this->content)
        this->content->SetParent(NULL_CONTROL);
    this->content = &control;
    this->RequestUpdate();
}

Control &Button::GetContent(void) {
    return *this->content;
}

void Button::SetBackColor(const Color &color) {
    if(this->backColor != color) {
        this->backColor = color;
        this->RequestUpdate();
    }
}

const Color &Button::GetBackColor(void) {
    return this->backColor;
}

void Button::SetBorderColor(const Color &color) {
    if(this->borderColor != color) {
        this->borderColor = color;
        this->RequestUpdate();
    }
}

const Color &Button::GetBorderColor(void) {
    return this->borderColor;
}

void Button::SetBorderSize(const uint8_t value) {
    if(this->borderSize != value) {
        this->borderSize = value;
        this->RequestUpdate();
    }
}

uint8_t Button::GetBorderSize(void) {
    return this->borderSize;
}

void Button::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    if(width >= 0) {
        this->SetActualWidth(width);
        if(this->content)
            this->content->UpdateActualWidth(width);
    }
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        width = MAX(referWidth - margin.Left - margin.Right, 0);
        this->SetActualWidth(width);
        if(this->content)
            this->content->UpdateActualWidth(width);
    }
    else {
        if(this->content)
            this->content->UpdateActualWidth(Size::None);
        if(this->content) {
            const Thickness &contentMargin = this->content->GetMargin();
            int16_t temp = this->content->GetActualSize().Width + contentMargin.Left + contentMargin.Right + this->borderSize * 2;
            this->SetActualWidth(MAX(temp, 0));
        }
        else
            this->SetActualWidth(0);
    }
}

void Button::UpdateActualHeight(int16_t referHeight) {
    int16_t height = this->GetSize().Height;
    if(height >= 0) {
        this->SetActualHeight(height);
        if(this->content)
            this->content->UpdateActualHeight(height);
    }
    else if((height == Size::None) && (referHeight >= 0)) {
        const Thickness &margin = this->GetMargin();
        height = MAX(referHeight - margin.Top - margin.Bottom, 0);
        this->SetActualHeight(height);
        if(this->content)
            this->content->UpdateActualHeight(height);
    }
    else {
        if(this->content)
            this->content->UpdateActualHeight(Size::None);
        if(this->content) {
            const Thickness &contentMargin = this->content->GetMargin();
            int16_t temp = this->content->GetActualSize().Height + contentMargin.Top + contentMargin.Bottom + this->borderSize * 2;
            this->SetActualHeight(MAX(temp, 0));
        }
        else
            this->SetActualHeight(0);
    }
}

void Button::UpdateLocation(void) {
    if(this->content) {
        const Thickness &objMargin = this->content->GetMargin();
        int16_t x = this->GetLoaction().X + objMargin.Left;
        int16_t y = this->GetLoaction().Y + objMargin.Top;
        this->content->SetLocation(x, y);
        this->content->UpdateLocation();
    }
}

void Button::OnDraw(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    if(this->borderColor.A != 0x00) {
        Pen pen(this->borderColor, this->borderSize);
        g.DrawRectangle(pen, Rect(actualSize));
    }
    if(this->backColor.A != 0x00) {
        int16_t width = actualSize.Width - this->borderSize * 2;
        int16_t height = actualSize.Height - this->borderSize * 2;
        g.FillRectangle(this->backColor, Rect(this->borderSize, this->borderSize, width, height));
    }
    if(this->content && this->content->GetVisible()) {
        const Size &objSize = this->content->GetActualSize();
        const Thickness &objMargin = this->content->GetMargin();
        int16_t left = MAX((actualSize.Width - objSize.Width) / 2, this->borderSize);
        int16_t top = MAX((actualSize.Height - objSize.Height) / 2, this->borderSize);
        int16_t width = actualSize.Width - this->borderSize * 2 - objMargin.Left - objMargin.Right;
        int16_t height = actualSize.Height - this->borderSize * 2 - objMargin.Top - objMargin.Bottom;

        Graphics btnGraph = g.SubGraphics(left, top, width, height);

        this->content->OnDraw(btnGraph);
    }
}
