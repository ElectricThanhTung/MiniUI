
#include "miniui_common.h"
#include "miniui_font.h"

static const uint8_t Font_Utf8ByteCount[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6,
};

uint8_t Font::Utf8ByteCount(char c) {
    return (c & 0x80) ? Font_Utf8ByteCount[((uint8_t)c - 0xC0) & 0xFC] : 1;
}

static uint32_t Font_Utf8Decode(const char *c) {
    if(*c & 0x80) {
        uint8_t byteCount = Font::Utf8ByteCount(*c);

        uint32_t code = *c & (0xFF >> (byteCount + 1));
        while(--byteCount) {
            c++;
            code <<= 6;
            code |= *c & 0x3F;
        }
        return code;
    }
    return *c;
}

bool CharInfo::GetPixel(uint8_t x, uint8_t y) const {
    uint32_t bitIndex = x + y * this->Width;
    return (this->Data[bitIndex / 8] >> (bitIndex % 8)) & 0x01;
}

Font::Font(const uint8_t *fontData) {
    this->data = (const FontData *)fontData;
    this->EmSize = this->data->StdHeight;
}

Font::Font(const uint8_t *fontData, uint16_t emSize) {
    this->data = (const FontData *)fontData;
    this->EmSize = emSize;
}

Font::Font(const Font &font) {
    this->data = font.data;
    this->EmSize = font.EmSize;
}

void Font::operator=(const Font &font) {
    this->data = font.data;
    this->EmSize = font.EmSize;
}

const CharInfo &Font::operator[](const char *c) const {
    uint32_t unicode = Font_Utf8Decode(c);
    uint32_t r = this->data->Count - 1;
    uint32_t l = 0;
    while(r >= l) {
        uint32_t mid = l + (r - l) / 2;
        const CharInfo *tmp = (CharInfo *)&((uint8_t *)this->data)[this->data->VectorTable[mid + 1]];
        if(tmp->Unicode == unicode)
            return *tmp;
        else if(tmp->Unicode > unicode)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return *(CharInfo *)0;
}

uint32_t Font::Count(void) const {
    return this->data->Count;
}

uint8_t Font::SpaceWidth(void) const {
    return this->data->SpaceWidth;
}

uint8_t Font::StdHeight() const {
    return this->data->StdHeight;
}

const Size Font::CalcSize(const char *text) const {
    int16_t width = 0;
    int16_t height = 0;
    uint8_t stdHeight = this->StdHeight();
    uint8_t space = this->SpaceWidth() * this->EmSize / stdHeight;
    space = MAX(space / 3, 1);

    while(*text) {
        const CharInfo &c = (*this)[text];
        text += Font::Utf8ByteCount(*text);
        if(*text)
            width += space;
        if(&c != 0) {
            int16_t c_width = c.Width * this->EmSize / stdHeight;
            int16_t c_height = c.Height * this->EmSize / stdHeight;
            int16_t c_yOffset = (c.Height + c.YOffset) * this->EmSize / stdHeight - c_height;
            width += c_width;
            int16_t tmp = c_height + ABS(c_yOffset);
            if(height < tmp)
                height = tmp;
        }
        else {
            width += (this->EmSize + 1) / 2;
            if(height < this->EmSize)
                height = this->EmSize;
        }
    }
    return Size(width, height);
}
