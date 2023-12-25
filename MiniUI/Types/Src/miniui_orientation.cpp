
#include "miniui_orientation.h"

Orientation::Orientation(void) {
    this->O = 0;
}

Orientation::Orientation(uint8_t value) {
    this->O = value;
}

Orientation::Orientation(const Orientation &value) {
    this->O = value.O;
}

void Orientation::operator=(const Orientation &value) {
    this->O = value.O;
}

bool Orientation::operator==(const Orientation &another) {
    return this->O == another.O;
}

bool Orientation::operator!=(const Orientation &another) {
    return this->O != another.O;
}

const Orientation Orientation::Horizontal = 0;
const Orientation Orientation::Vertical = 1;
const Orientation Orientation::None = 2;
