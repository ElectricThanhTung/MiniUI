
#ifndef __MINIUI_THICKNESS_H
#define __MINIUI_THICKNESS_H

#include <stdint.h>

class Thickness {
public:
    const int16_t Left;
    const int16_t Top;
    const int16_t Right;
    const int16_t Bottom;

    Thickness(void);
    Thickness(int16_t value);
    Thickness(int16_t left, int16_t top, int16_t right, int16_t bottom);
    Thickness(const Thickness &thickness);

    void operator=(const Thickness &thickness);
    bool operator==(int16_t value) const;
    bool operator!=(int16_t value) const;
};

#endif /* __MINIUI_THICKNESS_H */
