
#include "miniui_font_list.h"
#include "miniui_textbox.h"

TextBox::TextBox(void) :
Control(Size::Auto), padding(2),
backColor(Color::LightGray), foreColor(Color::Black), borderColor(Color::Gray),
font(MINIUI_FONT_DEFAULT) {
    this->text = 0;
    this->borderSize = 1;
    this->passwordChar = 0;
}

const char *TextBox::GetType(void) {
    return "TextBox";
}

void TextBox::SetText(const char *text) {
    this->text = text;
}

void TextBox::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &TextBox::GetBackColor(void) const {
    return this->backColor;
}

const char *TextBox::GetText(void) const {
    return this->text;
}

void TextBox::SetForeColor(const Color &color) {
    this->foreColor = color;
}

const Color &TextBox::GetForeColor(void) const {
    return this->foreColor;
}

void TextBox::SetFont(const Font &font) {
    this->font = font;
}

const Font &TextBox::GetFont(void) const {
    return this->font;
}

void TextBox::SetBorderColor(const Color &color) {
    this->borderColor = color;
}

const Color &TextBox::GetBorderColor(void) const {
    return this->borderColor;
}

void TextBox::SetBorderSize(const uint8_t value) {
    this->borderSize = value;
}

uint8_t TextBox::GetBorderSize(void) const {
    return this->borderSize;
}

void TextBox::SetPasswordChar(const char value) {
    this->passwordChar = value;
}

const char TextBox::GetPasswordChar(void) const {
    return this->passwordChar;
}

void TextBox::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    if(width >= 0)
        this->SetActualWidth(width);
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualWidth(MiniUI_MAX(referWidth - margin.Top - margin.Bottom, 0));
    }
    else {
        if(this->text) {
            if(this->passwordChar == 0)
                this->SetActualWidth(this->font.CalcSize(this->text).Width + this->padding.Left + this->padding.Right + this->borderSize * 2);
            else {
                uint32_t length = MiniUI_StrLen(this->text);
                int16_t tmp = this->font.CalcSize((const char *)&this->passwordChar, 1).Width;
                uint8_t space = this->font.SpaceWidth() * font.EmSize / this->font.StdHeight();
                space = MiniUI_MAX(space / 4, 1);
                tmp = ((tmp + space) * length) - space;
                this->SetActualWidth(tmp + this->padding.Left + this->padding.Right + this->borderSize * 2);
            }
        }
        else
            this->SetActualWidth(0);
    }
}

void TextBox::UpdateActualHeight(int16_t referHeight) {
    int16_t height = this->GetSize().Height;
    if(height >= 0)
        this->SetActualHeight(height);
    else if((height == Size::None) && (referHeight >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualHeight(MiniUI_MAX(referHeight - margin.Top - margin.Bottom, 0));
    }
    else {
        int16_t height = this->font.EmSize + (this->font.EmSize + 1) / 2;
        this->SetActualHeight(height + this->padding.Top + this->padding.Bottom + this->borderSize * 2);
    }
}

void TextBox::OnDraw(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    if((this->borderColor.A != 0x00) && (this->borderSize > 0))
        g.DrawRectangle(Pen(this->borderColor, this->borderSize), actualSize);
    if(this->backColor.A != 0x00) {
        int16_t width = actualSize.Width - this->borderSize * 2;
        int16_t height = actualSize.Height - this->borderSize * 2;
        g.FillRectangle(this->backColor, Rect(this->borderSize, this->borderSize, width, height));
    }
    if(this->text) {
        int16_t graphX1 = MiniUI_MAX(this->borderSize + this->padding.Left, this->borderSize);
        int16_t graphY1 = MiniUI_MAX(this->borderSize + this->padding.Top, this->borderSize);
        int16_t graphX2 = actualSize.Width - this->borderSize - this->padding.Right;
        int16_t graphY2 = actualSize.Height - this->borderSize - this->padding.Bottom;
        int16_t width = graphX2 - this->borderSize - this->padding.Left;
        int16_t y = (actualSize.Height - this->borderSize * 2 - this->padding.Top - this->padding.Bottom - font.EmSize) / 2;
        Graphics tbGraph = g.SubGraphics(graphX1, graphY1, graphX2, graphY2);
        if(this->passwordChar == 0) {
            const Size textSize = font.CalcSize(this->text);
            int16_t x = (textSize.Width > width) ? (width - textSize.Width) : 0;
            tbGraph.DrawString(this->text, this->font, this->foreColor, Rect(x, y, textSize.Width, textSize.Height));
        }
        else {
            uint32_t length = MiniUI_StrLen(this->text);
            uint8_t space = this->font.SpaceWidth() * font.EmSize / this->font.StdHeight();
            space = MiniUI_MAX(space / 4, 1);
            const Size textSize = this->font.CalcSize((const char *)&this->passwordChar, 1);
            int16_t textWidth = ((textSize.Width + space) * length) - space;
            int16_t x = (textWidth > width) ? (width - textWidth) : 0;
            while(length) {
                tbGraph.DrawString((const char *)&this->passwordChar, this->font, this->foreColor, Rect(x, y, textSize.Width, textSize.Height));
                x += textSize.Width + space;
                length--;
            }
        }
    }
}
