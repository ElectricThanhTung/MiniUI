
#include "miniui_graphics.h"

#if __has_include("miniui_conf.h")
#include "miniui_conf.h"
#endif

#ifndef MINIUI_ANTI_ALIASING
#define MINIUI_ANTI_ALIASING            1
#warning "MINIUI_ANTI_ALIASING is not defined. Default value will be used"
#endif /* MINIUI_ANTI_ALIASING */

Graphics::Graphics(const Size &size, RgbColor *buffer) :
dataWidth(size.Width), left(0), top(0), width(size.Width), height(size.Height),
x(0), y(0), drawableX(0), drawableY(0), data(buffer) {

}

Graphics::Graphics(const Rect &rect, RgbColor *buffer) :
dataWidth(rect.Width), left(rect.Left), top(rect.Top), width(rect.Width), height(rect.Height),
x(0), y(0), drawableX(0), drawableY(0), data(buffer) {

}

Graphics::Graphics(const Graphics &g) :
dataWidth(g.dataWidth), left(g.left), top(g.top), width(g.width), height(g.height),
x(0), y(0), drawableX(0), drawableY(0), data(g.data) {

}

Graphics::Graphics(const Rect &rect, RgbColor *buffer, uint16_t dataWidth, const Point &origin, const Point &drawable) :
dataWidth(dataWidth), left(rect.Left), top(rect.Top), width(rect.Width), height(rect.Height),
x(origin.X), y(origin.Y), drawableX(drawable.X), drawableY(drawable.Y), data(buffer) {

}

Graphics Graphics::SubGraphics(const Rect &area) {
    return this->SubGraphics(area.Left, area.Top, area.Left + area.Width, area.Top + area.Height);
}

Graphics Graphics::SubGraphics(int16_t x, int16_t y) {
    x += this->x;
    y += this->y;
    const Point drawable(MiniUI_MAX(x, this->drawableX), MiniUI_MAX(y, this->drawableY));

    Graphics ret(Rect(this->left, this->top, this->width, this->height), this->data, this->dataWidth, Point(x, y), drawable);
    return ret;
}

Graphics Graphics::SubGraphics(int16_t x1, int16_t y1, uint16_t x2, uint16_t y2) {
    x1 += this->x;
    y1 += this->y;
    int16_t w = MiniUI_MIN(this->left + this->width, x2 + this->x) - this->left;
    int16_t h = MiniUI_MIN(this->top + this->height, y2 + this->y) - this->top;
    const Point drawable(MiniUI_MAX(x1, this->drawableX), MiniUI_MAX(y1, this->drawableY));

    Graphics ret(Rect(this->left, this->top, w, h), this->data, this->dataWidth, Point(x1, y1), drawable);
    return ret;
}

void Graphics::Clear(void) {
    RgbColor *data = this->data;
    for(uint16_t y = 0; y < this->height; y++) {
        uint32_t temp = y * this->dataWidth;
        for(uint16_t x = 0; x < this->width; x++)
            data[x + temp] = 0;
    }
}

void Graphics::DrawPixel(const Point &point, const Color &color) {
    int16_t x = point.X + this->x - this->left;
    if((x < this->width) && (x >= 0) && (x >= this->drawableX)) {
        int16_t y = point.Y + this->y - this->top;
        if((y < this->height) && (y >= 0) && (y >= this->drawableY)) {
            if(color.A == 0xFF)
                this->data[x + y * this->dataWidth] = color.RGB;
            else {
                RgbColor &pixel = this->data[x + y * this->dataWidth];
                uint8_t r = color.A * (color.R - pixel.R) / 255 + pixel.R;
                uint8_t g = color.A * (color.G - pixel.G) / 255 + pixel.G;
                uint8_t b = color.A * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }
    }
}

void Graphics::DrawLine(const Pen &pen, const Line &line) {
    const Point p1(line.X1 - this->left, line.Y1 - this->top);
    const Point p2(line.X2 - this->left, line.Y2 - this->top);
    RgbColor *dataBuff = this->data;
    const Color &color = pen.Color;

    if(color.A == 0xFF) {
        const RgbColor &rgb = color.RGB;
        if(p1.X == p2.X) {
            if((p1.X < 0) || (p1.X >= this->width))
                return;
            int16_t y1 = MiniUI_MAX(MiniUI_MIN(p1.Y, p2.Y), 0);
            int16_t y2 = MiniUI_MIN(MiniUI_MAX(p1.Y, p2.Y), this->height - 1);
            for(; y1 <= y2; y1++)
                dataBuff[p1.X + y1 * this->dataWidth] = rgb;
        }
        else if(p1.Y == p2.Y) {
            if((p1.Y < 0) || (p1.Y >= this->height))
                return;
            int16_t x1 = MiniUI_MAX(MiniUI_MIN(p1.X, p2.X), 0);
            int16_t x2 = MiniUI_MIN(MiniUI_MAX(p1.X, p2.X), this->width - 1);
            int32_t tmp = p1.Y * this->dataWidth;
            for(; x1 <= x2; x1++)
                dataBuff[x1 + tmp] = rgb;
        }
        else {
            int16_t x = p1.X;
            int16_t y = p1.Y;
            int16_t dx = MiniUI_ABS(p2.X - p1.X);
            int16_t dy = MiniUI_ABS(p2.Y - p1.Y);
            int8_t x_unit = (p1.X < p2.X) ? 1 : -1;
            int8_t y_unit = (p1.Y < p2.Y) ? 1 : -1;
            if(dx >= dy) {
                int16_t p = 2 * dy - dx;
                if((x >= 0) && (y >= 0) && (x < this->width) && (y < this->height))
                    dataBuff[x + y * this->dataWidth] = rgb;
                while(x != p2.X) {
                    if(p < 0)
                        p += 2 * dy;
                    else {
                        p += 2 * (dy - dx);
                        y += y_unit;
                    }
                    x += x_unit;
                    if((x >= 0) && (y >= 0) && (x < this->width) && (y < this->height))
                        dataBuff[x + y * this->dataWidth] = rgb;
                }
            }
            else {
                int16_t p = 2 * dx - dy;
                if((x >= 0) && (y >= 0) && (x < this->width) && (y < this->height))
                    dataBuff[x + y * this->dataWidth] = rgb;
                while(y != p2.Y) {
                    if(p < 0)
                        p += 2 * dx;
                    else {
                        p += 2 * (dx - dy);
                        x += x_unit;
                    }
                    y += y_unit;
                    if((x >= 0) && (y >= 0) && (x < this->width) && (y < this->height))
                        dataBuff[x + y * this->dataWidth] = rgb;
                }
            }
        }
    }
    else {
        // TODO
    }
}

void Graphics::DrawRectangle(const Pen &pen, const Rect &rect) {
    int16_t absX = rect.Left + this->x;
    int16_t absY = rect.Top + this->y;
    int16_t x1 = MiniUI_MAX(absX, this->left, this->x, this->drawableX) - this->left;
    int16_t y1 = MiniUI_MAX(absY, this->top, this->y, this->drawableY) - this->top;
    int16_t x2 = MiniUI_MIN(absX + rect.Width, this->left + this->width) - this->left;
    int16_t y2 = MiniUI_MIN(absY + rect.Height, this->top + this->height) - this->top;
    int32_t temp;
    RgbColor *dataBuff = this->data;

    if(pen.Color.A == 0xFF) {
        const RgbColor &rgb = pen.Color.RGB;
        if((absX >= this->left) && (absX < (this->left + this->width)) && (x1 < this->width)) {
            for(int16_t y = y1; y < y2; y++)
                dataBuff[y * this->dataWidth + x1] = rgb;
        }

        if((absY >= this->top) && (absY < (this->top + this->height)) && (y1 < this->height)) {
            temp = y1 * this->dataWidth;
            for(int16_t x = x1; x < x2; x++)
                dataBuff[temp + x] = rgb;
        }

        temp = absX + rect.Width - 1 - this->left;
        if((temp >= 0) && (temp < this->width)) {
            for(int16_t y = y1; y < y2; y++)
                dataBuff[y * this->dataWidth + temp] = rgb;
        }

        temp = absY + rect.Height - 1 - this->top;
        if((temp >= 0) && (temp < this->height)) {
            temp *= this->dataWidth;
            for(int16_t x = x1; x < x2; x++)
                dataBuff[temp + x] = rgb;
        }
    }
    else {
        const Color &color = pen.Color;
        if((absX >= this->left) && (absX < (this->left + this->width)) && (x1 < this->width)) {
            for(int16_t y = y1; y < y2; y++) {
                RgbColor &pixel = dataBuff[y * this->dataWidth + x1];
                uint8_t r = color.A * (color.R - pixel.R) / 255 + pixel.R;
                uint8_t g = color.A * (color.G - pixel.G) / 255 + pixel.G;
                uint8_t b = color.A * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }

        if((absY >= this->top) && (absY < (this->top + this->height)) && (y1 < this->height)) {
            temp = y1 * this->dataWidth;
            for(int16_t x = x1; x < x2; x++) {
                RgbColor &pixel = dataBuff[temp + x];
                uint8_t r = color.A * (color.R - pixel.R) / 255 + pixel.R;
                uint8_t g = color.A * (color.G - pixel.G) / 255 + pixel.G;
                uint8_t b = color.A * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }

        temp = absX + rect.Width - 1 - this->left;
        if((temp >= 0) && (temp < this->width)) {
            for(int16_t y = y1; y < y2; y++) {
                RgbColor &pixel = dataBuff[y * this->dataWidth + temp];
                uint8_t r = color.A * (color.R - pixel.R) / 255 + pixel.R;
                uint8_t g = color.A * (color.G - pixel.G) / 255 + pixel.G;
                uint8_t b = color.A * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }

        temp = absY + rect.Height - 1 - this->top;
        if((temp >= 0) && (temp < this->height)) {
            temp *= this->dataWidth;
            for(int16_t x = x1; x < x2; x++) {
                RgbColor &pixel = dataBuff[temp + x];
                uint8_t r = color.A * (color.R - pixel.R) / 255 + pixel.R;
                uint8_t g = color.A * (color.G - pixel.G) / 255 + pixel.G;
                uint8_t b = color.A * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }
    }
}

void Graphics::FillRectangle(const Color &color, const Rect &rect) {
    int16_t absX = rect.Left + this->x;
    int16_t absY = rect.Top + this->y;
    int16_t x1 = MiniUI_MAX(absX, this->left, this->x, this->drawableX) - this->left;
    int16_t x2 = MiniUI_MIN(absX + rect.Width, this->left + this->width) - this->left;

    if(x1 >= x2)
        return;

    int16_t y1 = MiniUI_MAX(absY, this->top, this->y, this->drawableY) - this->top;
    int16_t y2 = MiniUI_MIN(absY + rect.Height, this->top + this->height) - this->top;

    RgbColor *dataBuff = this->data;
    
    if(color.A == 0xFF) {
        const RgbColor &rgb = color.RGB;
        for(int16_t y = y1; y < y2; y++) {
            int32_t tmp = y * this->dataWidth;
            for(int16_t x = x1; x < x2; x++)
                dataBuff[x + tmp] = rgb;
        }
    }
    else {
        for(int16_t y = y1; y < y2; y++) {
            int32_t tmp = y * this->dataWidth;
            for(int16_t x = x1; x < x2; x++) {
                RgbColor &pixel = dataBuff[x + tmp];
                uint8_t r = color.A * (color.R - pixel.R) / 255 + pixel.R;
                uint8_t g = color.A * (color.G - pixel.G) / 255 + pixel.G;
                uint8_t b = color.A * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }
    }
}

void Graphics::DrawChar(const CharInfo &c, const Color &color, const Rect &rect) {
    int16_t absX = rect.Left + this->x;
    int16_t absY = rect.Top + this->y;

    int16_t x1 = MiniUI_MAX(absX, this->left, this->x, this->drawableX) - this->left;
    int16_t x2 = MiniUI_MIN(absX + rect.Width, this->left + this->width) - this->left;
    if(x1 >= x2)
        return;

    int16_t y1 = MiniUI_MAX(absY, this->top, this->y, this->drawableY) - this->top;
    int16_t y2 = MiniUI_MIN(absY + rect.Height, this->top + this->height) - this->top;
    if(y1 >= y2)
        return;

    RgbColor *dataBuff = this->data;

    for(int16_t y = y1; y < y2; y++) {
        int16_t c_y = (y - (absY - this->top)) * c.Height / rect.Height;
        int32_t tmp =  y * this->dataWidth;
        for(int16_t x = x1; x < x2; x++) {
            uint8_t p = 0;
            int16_t c_x = (x - (absX - this->left)) * c.Width / rect.Width;
            RgbColor &pixel = dataBuff[x + tmp];
            if(c.GetPixel(c_x, c_y))
                p = color.A;
#if (MINIUI_ANTI_ALIASING == 1)
            else {
                p = (c_x > 0) ? c.GetPixel(c_x - 1, c_y) : 0;
                p += (c_y > 0) ? c.GetPixel(c_x, c_y - 1) : 0;
                p += ((c_x + 1) < c.Width) ? c.GetPixel(c_x + 1, c_y) : 0;
                p += ((c_y + 1) < c.Height) ? c.GetPixel(c_x, c_y + 1) : 0;
                p = p * color.A / 5;
            }
#endif
            if(p) {
                uint16_t r = p * (color.R - pixel.R) / 255 + pixel.R;
                uint16_t g = p * (color.G - pixel.G) / 255 + pixel.G;
                uint16_t b = p * (color.B - pixel.B) / 255 + pixel.B;
                pixel = RgbColor(r, g, b);
            }
        }
    }
}

void Graphics::DrawString(const char *text, const Font &font, const Color &color, const Rect &rect) {
    int16_t right = MiniUI_MIN(this->left + this->width, rect.Left + this->x + rect.Width);
    if((rect.Left + this->x) >= right)
        return;

    int16_t bottom = MiniUI_MIN(this->top + this->height, rect.Top + this->y + rect.Height);
    if((rect.Top + this->y) >= bottom)
        return;

    int16_t x = rect.Left;
    uint8_t stdHeight = font.StdHeight();
    uint8_t space = font.SpaceWidth() * font.EmSize / stdHeight;
    space = MiniUI_MAX(space / 4, 1);

    while(*text) {
        if(x >= right)
            return;
        const CharInfo *c = &(font[text]);
        if(c != 0) {
            int16_t width = c->Width * font.EmSize / stdHeight;
            int16_t height = c->Height * font.EmSize / stdHeight;
            int16_t yOffset = (c->Height + c->YOffset) * font.EmSize / stdHeight - height;
            if(*text == ' ')
                width = MiniUI_MAX(width - space * 2, space * 2);
            this->DrawChar(*c, color, Rect(x, rect.Top + yOffset, width, height));
            x += width + space;
        }
        else {
            int16_t width = (font.EmSize + 1) / 2;
            this->FillRectangle(color, Rect(x, rect.Top, width, font.EmSize));
            x += width + space;
        }
        text += Font::Utf8ByteCount(*text);
    }
}

void Graphics::DrawString(const char *text, uint32_t length, const Font &font, const Color &color, const Rect &rect) {
    int16_t right = MiniUI_MIN(this->left + this->width, rect.Left + this->x + rect.Width);
    int16_t bottom = MiniUI_MIN(this->top + this->height, rect.Top + this->y + rect.Height);

    if(((rect.Left + this->x) >= right) || ((rect.Top + this->y) >= bottom))
        return;

    int16_t x = rect.Left;
    uint8_t stdHeight = font.StdHeight();
    uint8_t space = font.SpaceWidth() * font.EmSize / stdHeight;
    space = MiniUI_MAX(space / 4, 1);

    while((*text) && length) {
        if(x >= right)
            return;
        const CharInfo *c = &(font[text]);
        length--;
        if(c != 0) {
            int16_t width = c->Width * font.EmSize / stdHeight;
            int16_t height = c->Height * font.EmSize / stdHeight;
            int16_t yOffset = (c->Height + c->YOffset) * font.EmSize / stdHeight - height;
            if(*text == ' ')
                width = MiniUI_MAX(width - space * 2, space * 2);
            this->DrawChar(*c, color, Rect(x, rect.Top + yOffset, width, height));
            x += width + space;
        }
        else {
            int16_t width = (font.EmSize + 1) / 2;
            this->FillRectangle(color, Rect(x, rect.Top, width, font.EmSize));
            x += width + space;
        }
        text += Font::Utf8ByteCount(*text);
    }
}
