
#ifndef __MINIUI_SIZE_H
#define __MINIUI_SIZE_H

#include <stdint.h>

class Size {
public:
    const int16_t Width;
    const int16_t Height;

    Size(void);
    Size(int16_t uniformSize);
    Size(int16_t width, int16_t height);
    Size(const Size &size);

    void operator=(const Size &size);

    static const int16_t None;
    static const int16_t Auto;
};

#endif /* __MINIUI_SIZE_H */
