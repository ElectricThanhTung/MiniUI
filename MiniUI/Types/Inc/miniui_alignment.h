
#ifndef __MINIUI_ALIGNMENT_H
#define __MINIUI_ALIGNMENT_H

#include <stdint.h>

class VerticalAlignment {
private:
    uint8_t alignment;

    VerticalAlignment(uint8_t value);
public:
    VerticalAlignment(void);
    VerticalAlignment(const VerticalAlignment &value);

    void operator=(const VerticalAlignment &value);
    bool operator==(const VerticalAlignment &another) const;
    bool operator!=(const VerticalAlignment &another) const;

    static const VerticalAlignment Top;
    static const VerticalAlignment Center;
    static const VerticalAlignment Bottom;
};

class HorizontalAlignment {
private:
    uint8_t alignment;

    HorizontalAlignment(uint8_t value);
public:
    HorizontalAlignment(void);
    HorizontalAlignment(const HorizontalAlignment &value);

    void operator=(const HorizontalAlignment &value);
    bool operator==(const HorizontalAlignment &another) const;
    bool operator!=(const HorizontalAlignment &another) const;

    static const HorizontalAlignment Left;
    static const HorizontalAlignment Center;
    static const HorizontalAlignment Right;
};

#endif /* __MINIUI_ALIGNMENT_H */
