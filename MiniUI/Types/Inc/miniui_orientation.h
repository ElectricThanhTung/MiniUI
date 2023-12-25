
#ifndef __MINIUI_ORIENTATION_H
#define __MINIUI_ORIENTATION_H

#include <stdint.h>

class Orientation {
private:
    uint8_t O;

    Orientation(uint8_t value);
public:
    Orientation(void);
    Orientation(const Orientation &value);

    void operator=(const Orientation &value);
    bool operator==(const Orientation &another);
    bool operator!=(const Orientation &another);

    static const Orientation Horizontal;
    static const Orientation Vertical;
    static const Orientation None;
};

#endif /* __MINIUI_ORIENTATION_H */
