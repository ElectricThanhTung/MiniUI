
#include "miniui_font_list.h"
#include "miniui_button.h"
#include "miniui_collections.h"

Button::Button(void) :
Control(Size::Auto),
backColor(Color::LightGray), borderColor(Color::Gray), foreColor(Color::Black),
font(MINIUI_FONT_DEFAULT) {
    this->content = 0;
    this->text = 0;
    this->borderSize = 1;
}

Button::Button(Control &content) :
Control(Size::Auto),
backColor(Color::LightGray), borderColor(Color::Gray), foreColor(Color::Black),
font(MINIUI_FONT_DEFAULT) {
    this->content = &content;
    this->text = 0;
    this->borderSize = 1;
}

Button::Button(const char *text) :
Control(Size::Auto),
backColor(Color::LightGray), borderColor(Color::Gray), foreColor(Color::Black),
font(MINIUI_FONT_DEFAULT) {
    this->content = 0;
    this->text = text;
    this->borderSize = 1;
}

Button::Button(const char *text, const Color &foreColor) :
Control(Size::Auto),
backColor(Color::LightGray), borderColor(Color::Gray), foreColor(foreColor),
font(MINIUI_FONT_DEFAULT) {
    this->content = 0;
    this->text = text;
    this->borderSize = 1;
}

Button::Button(const char *text, const Color &foreColor, const ::Font &font) :
Control(Size::Auto),
backColor(Color::LightGray), borderColor(Color::Gray), foreColor(foreColor),
font(font) {
    this->content = 0;
    this->text = text;
    this->borderSize = 1;
}

const char *Button::GetType(void) {
    return "Button";
}

void Button::SetContent(const char *text) {
    this->text = text;
    if(this->content)
        this->content->SetParent(NULL_CONTROL);
    this->content = 0;
}

void Button::SetContent(Control &control) {
    Collections *objParentList = (Collections *)control.GetParentList();
    control.SetParent(*this);
    if(objParentList)
        objParentList->Remove(control);
    if(this->content)
        this->content->SetParent(NULL_CONTROL);
    this->content = &control;
    this->text = 0;
}

void *Button::GetContent(void) const {
    return this->content ? this->content : (void *)this->text;
}

void Button::SetForeColor(const Color &color) {
    this->foreColor = color;
}

const Color &Button::GetForeColor(void) const {
    return this->foreColor;
}

void Button::SetFont(const Font &font) {
    this->font = font;
}

const Font &Button::GetFont(void) const {
    return this->font;
}

void Button::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &Button::GetBackColor(void) const {
    return this->backColor;
}

void Button::SetBorderColor(const Color &color) {
    this->borderColor = color;
}

const Color &Button::GetBorderColor(void) const {
    return this->borderColor;
}

void Button::SetBorderSize(const uint8_t value) {
    this->borderSize = value;
}

uint8_t Button::GetBorderSize(void) const {
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
        width = MiniUI_MAX(referWidth - margin.Left - margin.Right, 0);
        this->SetActualWidth(width);
        if(this->content)
            this->content->UpdateActualWidth(width);
    }
    else {
        if(this->content) {
            this->content->UpdateActualWidth(Size::None);
            const Thickness &contentMargin = this->content->GetMargin();
            int16_t temp = this->content->GetActualSize().Width + contentMargin.Left + contentMargin.Right + this->borderSize * 2;
            this->SetActualWidth(MiniUI_MAX(temp, 0));
        }
        else if(this->text) {
            const Size textSize = font.CalcSize(this->text);
            this->SetActualWidth(textSize.Width + this->borderSize * 2);
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
        height = MiniUI_MAX(referHeight - margin.Top - margin.Bottom, 0);
        this->SetActualHeight(height);
        if(this->content)
            this->content->UpdateActualHeight(height);
    }
    else {
        if(this->content) {
            this->content->UpdateActualHeight(Size::None);
            const Thickness &contentMargin = this->content->GetMargin();
            int16_t temp = this->content->GetActualSize().Height + contentMargin.Top + contentMargin.Bottom + this->borderSize * 2;
            this->SetActualHeight(MiniUI_MAX(temp, 0));
        }
        else if(this->text) {
            const Size textSize = font.CalcSize(this->text);
            this->SetActualHeight(textSize.Height + this->borderSize * 2);
        }
        else
            this->SetActualHeight(0);
    }
}

void Button::OnDraw(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    if((this->borderColor.A != 0x00) && (this->borderSize > 0))
        g.DrawRectangle(Pen(this->borderColor, this->borderSize), actualSize);
    if(this->backColor.A != 0x00) {
        int16_t width = actualSize.Width - this->borderSize * 2;
        int16_t height = actualSize.Height - this->borderSize * 2;
        g.FillRectangle(this->backColor, Rect(this->borderSize, this->borderSize, width, height));
    }
    if(this->content) {
        if(this->content->GetVisible()) {
            const Size &objSize = this->content->GetActualSize();
            const Thickness &objMargin = this->content->GetMargin();
            const HorizontalAlignment objHorizAlign = this->content->GetHorizontalAlignment();
            const VerticalAlignment objVertAlign = this->content->GetVerticalAlignment();

            int16_t graphX2 = actualSize.Width - this->borderSize;
            int16_t graphY2 = actualSize.Height - this->borderSize;
            int16_t objX, objY;

            graphX2 = MiniUI_MIN(graphX2, graphX2 - objMargin.Right);
            graphY2 = MiniUI_MIN(graphY2, graphY2 - objMargin.Bottom);

            if(objHorizAlign == HorizontalAlignment::Left)
                objX = 0;
            else if(objHorizAlign == HorizontalAlignment::Center)
                objX = ((actualSize.Width - this->borderSize * 2) - objSize.Width) / 2 - objMargin.Right;
            else
                objX = ((actualSize.Width - this->borderSize * 2) - objSize.Width) - objMargin.Right;

            if(objVertAlign == VerticalAlignment::Top)
                objY = 0;
            else if(objVertAlign == VerticalAlignment::Center)
                objY = ((actualSize.Height - this->borderSize * 2) - objSize.Height) / 2 - objMargin.Bottom;
            else
                objY = ((actualSize.Height - this->borderSize * 2) - objSize.Height) - objMargin.Bottom;

            Graphics btnGraph = g.SubGraphics(
                this->borderSize,
                this->borderSize,
                graphX2,
                graphY2
            ).SubGraphics(
                objMargin.Left,
                objMargin.Top
            ).SubGraphics(
                objX,
                objY
            );
            this->content->OnDraw(btnGraph);
        }
    }
    else if(this->text) {
        const Size &actualSize = this->GetActualSize();
        const int16_t graphW = actualSize.Width - this->borderSize * 2;
        const int16_t graphH = actualSize.Height - this->borderSize * 2;
        const Size textSize = font.CalcSize(this->text);
        const Rect textRect(Point((graphW - textSize.Width) / 2, (graphH - textSize.Height) / 2), textSize);

        g.SubGraphics(
            this->borderSize,
            this->borderSize,
            actualSize.Width - this->borderSize,
            actualSize.Height - this->borderSize
        ).DrawString(this->text, this->font, this->foreColor, textRect);
    }
}
