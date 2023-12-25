
#ifndef __MINIUI_COLLECTIONS_H
#define __MINIUI_COLLECTIONS_H

#include <stdint.h>
#include "miniui_control.h"

class Collections {
private:
    Control *Parent;
    Control *End;
    Control *Current;
    uint16_t Index;

    Collections(const Collections &) = delete;
    void operator=(const Collections &) = delete;
public:
    const uint16_t Count;

    Collections(Control &parent);

    void Add(Control &obj);
    void Remove(Control &obj);
    void RemoveAt(uint16_t index);

    Control &operator[](uint16_t index);
};

#endif /* __MINIUI_COLLECTIONS_H */
