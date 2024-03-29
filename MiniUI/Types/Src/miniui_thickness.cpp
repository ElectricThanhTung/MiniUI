
#include <string.h>
#include "miniui_thickness.h"

Thickness::Thickness(void) : Left(0), Top(0), Right(0), Bottom(0) {

}

Thickness::Thickness(int16_t uniformSize) : Left(uniformSize), Top(uniformSize), Right(uniformSize), Bottom(uniformSize) {

}

Thickness::Thickness(int16_t left, int16_t top, int16_t right, int16_t bottom) : Left(left), Top(top), Right(right), Bottom(bottom) {

}

Thickness::Thickness(const Thickness &thickness) : Left(thickness.Left), Top(thickness.Top), Right(thickness.Right), Bottom(thickness.Bottom) {

}

void Thickness::operator=(const Thickness &thickness) {
    memcpy((void *)this, &thickness, sizeof(*this));
}

bool Thickness::operator==(int16_t value) const {
    return (this->Left == value) && (this->Top == value) && (this->Right == value) && (this->Bottom == value);
}

bool Thickness::operator!=(int16_t value) const {
    return (this->Left != value) || (this->Top != value) || (this->Right != value) || (this->Bottom != value);
}
