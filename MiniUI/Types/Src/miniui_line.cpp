
#include <string.h>
#include "miniui_line.h"

Line::Line(void) : X1(0), Y1(0), X2(0), Y2(0) {

}

Line::Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) : X1(x1), Y1(y1), X2(x2), Y2(y2) {

}

Line::Line(const Point &point1, const Point &point2) : Point1(point1), Point2(point2) {

}

Line::Line(const Line &line) : Point1(line.Point1), Point2(line.Point2) {

}

void Line::operator=(const Line &line) {
    memcpy((void *)this, &line, sizeof(*this));
}
