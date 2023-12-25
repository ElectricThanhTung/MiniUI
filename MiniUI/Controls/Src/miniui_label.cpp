
#include "miniui_font_list.h"
#include "miniui_label.h"

Label::Label(void) : Control(Size::AutoSize), foreColor(Color::Black), font(FONT_DEFAULT) {
    this->text = 0;
}

Label::Label(const Label &&label) : Control(Size::AutoSize), foreColor(label.foreColor), font(label.font), margin(label.margin) {
    this->text = label.text;
}

Label::Label(const char *text) : Control(Size::AutoSize), foreColor(Color::Black), font(FONT_DEFAULT), margin(1) {
    this->text = text;
}

Label::Label(const char *text, const Color &foreColor) : Control(Size::AutoSize), foreColor(foreColor), font(FONT_DEFAULT), margin(1) {
    this->text = text;
}

Label::Label(const char *text, const Color &foreColor, const Font &font) : Control(Size::AutoSize), foreColor(foreColor), font(font), margin(1) {
    this->text = text;
}

void Label::SetText(const char *text) {
    this->text = text;
}

const char *Label::GetText(void) {
    return this->text;
}

void Label::SetForeColor(const Color &color) {
    this->foreColor = color;
}

const Color &Label::GetForeColor(void) {
    return this->foreColor;
}

void Label::SetFont(const Font &font) {
    this->font = font;
}

const Font &Label::GetFont(void) {
    return this->font;
}

void Label::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    if(width >= 0)
        this->SetActualWidth(width);
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualWidth(MAX(referWidth - margin.Top - margin.Bottom, 0));
    }
    else {
        if(this->text)
            this->SetActualWidth(this->font.CalcSize(this->text).Width);
        else
            this->SetActualWidth(0);
    }
}

void Label::UpdateActualHeight(int16_t referHeight) {
    int16_t height = this->GetSize().Height;
    if(height >= 0)
        this->SetActualHeight(height);
    else if((height == Size::None) && (referHeight >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualHeight(MAX(referHeight - margin.Top - margin.Bottom, 0));
    }
    else {
        if(this->text)
            this->SetActualHeight(this->font.CalcSize(this->text).Height);
        else
            this->SetActualHeight(0);
    }
}

void Label::OnDraw(Graphics &g) {
    if(this->text) {
        const Size &actualSize = this->GetActualSize();
        g.DrawString(this->text, this->font, this->foreColor, Rect(actualSize));
    }
}
