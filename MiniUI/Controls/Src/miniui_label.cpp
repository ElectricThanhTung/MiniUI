
#include "miniui_font_list.h"
#include "miniui_label.h"

Label::Label(void) : Control(Size::Auto), foreColor(Color::Black), font(MINIUI_FONT_DEFAULT) {
    this->text = 0;
}

Label::Label(const char *text) : Control(Size::Auto), foreColor(Color::Black), font(MINIUI_FONT_DEFAULT) {
    this->text = text;
    this->SetMargin(Thickness(1));
}

Label::Label(const char *text, const Color &foreColor) : Control(Size::Auto), foreColor(foreColor), font(MINIUI_FONT_DEFAULT) {
    this->text = text;
    this->SetMargin(Thickness(1));
}

Label::Label(const char *text, const Color &foreColor, const Font &font) : Control(Size::Auto), foreColor(foreColor), font(font) {
    this->text = text;
    this->SetMargin(Thickness(1));
}

const char *Label::GetType(void) {
    return "Label";
}

void Label::SetText(const char *text) {
    this->text = text;
}

const char *Label::GetText(void) const {
    return this->text;
}

void Label::SetForeColor(const Color &color) {
    this->foreColor = color;
}

const Color &Label::GetForeColor(void) const {
    return this->foreColor;
}

void Label::SetFont(const Font &font) {
    this->font = font;
}

const Font &Label::GetFont(void) const {
    return this->font;
}

void Label::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    if(width >= 0)
        this->SetActualWidth(width);
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualWidth(MiniUI_MAX(referWidth - margin.Top - margin.Bottom, 0));
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
        this->SetActualHeight(MiniUI_MAX(referHeight - margin.Top - margin.Bottom, 0));
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
        g.DrawString(this->text, this->font, this->foreColor, actualSize);
    }
}
