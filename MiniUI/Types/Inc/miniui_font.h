
#ifndef __MINIUI_FONT_H
#define __MINIUI_FONT_H

#include <stdint.h>
#include "miniui_size.h"

struct CharInfo {
public:
    const uint32_t Unicode;
    const uint8_t Width;
    const uint8_t Height;
    const int8_t YOffset;
    const uint8_t Data[];

    bool GetPixel(uint8_t x, uint8_t y) const;
private:
    CharInfo(void) = delete;
    CharInfo(const CharInfo &) = delete;
};

class FontData {
public:
    const uint32_t Count : 16;
    const uint32_t SpaceWidth : 8;
    const uint32_t StdHeight : 8;
    const uint32_t VectorTable[];
private:
    FontData(void);
    FontData(FontData &);
};

class Font {
private:
    const FontData *data;
public:
    uint16_t EmSize;

    Font(const uint8_t *fontData);
    Font(const uint8_t *fontData, uint16_t emSize);
    Font(const Font &font);

    void operator=(const Font &font);

    const CharInfo &operator[](const char *c) const;

    bool operator==(const Font &font);
    bool operator!=(const Font &font);

    uint32_t Count(void) const;
    uint8_t SpaceWidth(void) const;
    uint8_t StdHeight() const;
    const Size CalcSize(const char *text) const;

    static uint8_t Utf8ByteCount(char c);
};

#endif /* __MINIUI_FONT_H */
