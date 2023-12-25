
#include <string.h>
#include "miniui_point.h"

Point::Point(void) : X(0), Y(0) {

}

Point::Point(int16_t x, int16_t y) : X(x), Y(y) {
    
}

Point::Point(const Point &point) : X(point.X), Y(point.Y) {
    
}

void Point::operator=(const Point &point) {
    memcpy((void *)this, &point, sizeof(*this));
}
