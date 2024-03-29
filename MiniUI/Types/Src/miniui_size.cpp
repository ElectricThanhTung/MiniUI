
#include <string.h>
#include "miniui_size.h"

#define SIZE_NONE               -1
#define SIZE_AUTO               -2

Size::Size(void) : Width(SIZE_AUTO), Height(SIZE_AUTO) {

}

Size::Size(int16_t uniformSize) : Width(uniformSize), Height(uniformSize) {

}

Size::Size(int16_t width, int16_t height) : Width(width), Height(height) {

}

Size::Size(const Size &size) : Width(size.Width), Height(size.Height)  {

}

void Size::operator=(const Size &size) {
    memcpy((void *)this, &size, sizeof(*this));
}

const int16_t Size::None = SIZE_NONE;
const int16_t Size::Auto = SIZE_AUTO;
