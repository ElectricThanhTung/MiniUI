
#include "miniui_font_list.h"
#include "miniui_richtextbox.h"

RichTextBox::RichTextBox(void) :
Control(Size::Auto), padding(2),
backColor(Color::LightGray), foreColor(Color::Black), borderColor(Color::Gray),
font(MINIUI_FONT_DEFAULT) {
    this->text = 0;
    this->borderSize = 1;
    this->lineCount = 0;
}

const char *RichTextBox::GetType(void) {
    return "RichTextBox";
}

void RichTextBox::SetText(const char *text) {
    this->text = text;
}

const char *RichTextBox::GetText(void) const {
    return this->text;
}

void RichTextBox::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &RichTextBox::GetBackColor(void) const {
    return this->backColor;
}

void RichTextBox::SetForeColor(const Color &color) {
    this->foreColor = color;
}

const Color &RichTextBox::GetForeColor(void) const {
    return this->foreColor;
}

void RichTextBox::SetFont(const Font &font) {
    this->font = font;
}

const Font &RichTextBox::GetFont(void) const {
    return this->font;
}

void RichTextBox::SetBorderColor(const Color &color) {
    this->borderColor = color;
}

const Color &RichTextBox::GetBorderColor(void) const {
    return this->borderColor;
}

void RichTextBox::SetBorderSize(const uint8_t value) {
    this->borderSize = value;
}

uint8_t RichTextBox::GetBorderSize(void) const {
    return this->borderSize;
}

void RichTextBox::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    this->lineCount = 0;
    if(width >= 0)
        this->SetActualWidth(width);
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualWidth(MiniUI_MAX(referWidth - margin.Top - margin.Bottom, 0));
    }
    else {
        if(this->text) {
            const char *str = this->text;
            int16_t tmp = 0;
            uint8_t stdHeight = font.StdHeight();
            uint8_t space = this->font.SpaceWidth() * font.EmSize / stdHeight;
            space = MiniUI_MAX(space / 4, 1);
            width = 0;
            this->lineCount = 1;
            while(*str) {
                if(*str == '\n') {
                    if(width < tmp)
                        width = tmp;
                    tmp = 0;
                    this->lineCount++;
                }
                else if((*str) && (*str != '\r')) {
                    const CharInfo *c = &this->font[str];
                    tmp += ((c != 0) ? (c->Width * font.EmSize / stdHeight) : ((this->font.EmSize + 1) / 2)) + space;
                }
                str += Font::Utf8ByteCount(*str);
            }
            if(width < tmp)
                width = tmp;
            this->SetActualWidth(width + this->padding.Left + this->padding.Right + this->borderSize * 2);
        }
        else
            this->SetActualWidth(0);
    }
}

void RichTextBox::UpdateActualHeight(int16_t referHeight) {
    int16_t height = this->GetSize().Height;
    if(height >= 0)
        this->SetActualHeight(height);
    else if((height == Size::None) && (referHeight >= 0)) {
        const Thickness &margin = this->GetMargin();
        this->SetActualHeight(MiniUI_MAX(referHeight - margin.Top - margin.Bottom, 0));
    }
    else {
        if(this->text) {
            if(!this->lineCount) {
                this->lineCount = 1;
                const char *str = this->text;
                uint16_t index = 0;
                uint16_t length = 0;
                int16_t x = (this->borderSize + this->padding.Left) - MiniUI_MAX(this->borderSize + this->padding.Left, this->borderSize);
                int16_t width = this->GetActualSize().Width - this->borderSize * 2 - this->padding.Left - this->padding.Right;
                int16_t tmp = x;
                uint8_t space = this->font.SpaceWidth() * font.EmSize / this->font.StdHeight();
                space = MiniUI_MAX(space / 4, 1);
                while(str[index]) {
                    if((str[index] == ' ') || (str[index] == '\n')) {
                        int16_t strWidth = font.CalcSize(str, length).Width;
                        if((str[index] == '\n') || ((strWidth + tmp) > width)) {
                            this->lineCount++;
                            tmp = x + strWidth + space + this->font.SpaceWidth();
                        }
                        else
                            tmp += strWidth + space + this->font.SpaceWidth();
                        str += index + 1;
                        length = 0;
                        index = 0;
                    }
                    else {
                        length++;
                        index += Font::Utf8ByteCount(str[index]);
                    }
                }
                if(length) {
                    int16_t strWidth = font.CalcSize(str, length).Width;
                    if((strWidth + tmp) > width)
                        this->lineCount++;
                }
            }
            height = this->lineCount * (font.EmSize + (font.EmSize + 1) / 2);
            this->SetActualHeight(height + this->padding.Top + this->padding.Bottom + this->borderSize * 2);
        }
        else
            this->SetActualHeight(this->font.EmSize + this->padding.Top + this->padding.Bottom + this->borderSize * 2);
    }
    this->lineCount = 0;
}

void RichTextBox::OnDraw(Graphics &g) {
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
        Graphics tbGraph = g.SubGraphics(graphX1, graphY1, graphX2, graphY2);
        const char *str = this->text;
        uint16_t index = 0;
        uint16_t length = 0;
        int16_t x = (this->borderSize + this->padding.Left) - graphX1;
        int16_t y = ((this->borderSize + this->padding.Top) - graphY1) + ((font.EmSize + 2) / 4);
        int16_t tmp = x;
        uint8_t space = this->font.SpaceWidth() * font.EmSize / this->font.StdHeight();
        space = MiniUI_MAX(space / 4, 1);
        while(str[index]) {
            if((str[index] == ' ') || (str[index] == '\n')) {
                int16_t strWidth = font.CalcSize(str, length).Width;
                if((str[index] == '\n') || ((strWidth + tmp) > width)) {
                    y += font.EmSize + (font.EmSize + 1) / 2;
                    tbGraph.DrawString(str, length, this->font, this->foreColor, Rect(x, y, graphX2 - x + 1, graphY2 - y + 1));
                    tmp = x + strWidth + space + this->font.SpaceWidth();
                }
                else {
                    tbGraph.DrawString(str, length, this->font, this->foreColor, Rect(tmp, y, graphX2 - tmp + 1, graphY2 - y + 1));
                    tmp += strWidth + space + this->font.SpaceWidth();
                }
                str += index + 1;
                length = 0;
                index = 0;
            }
            else {
                length++;
                index += Font::Utf8ByteCount(str[index]);
            }
        }
        if(length) {
            int16_t strWidth = font.CalcSize(str, length).Width;
            if((strWidth + tmp) > width) {
                y += font.EmSize + (font.EmSize + 1) / 2;
                tmp = x;
            }
            tbGraph.DrawString(str, length, this->font, this->foreColor, Rect(tmp, y, graphX2 - tmp + 1, graphY2 - y + 1));
        }
    }
}
