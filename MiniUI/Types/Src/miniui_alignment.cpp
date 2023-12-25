
#include "miniui_alignment.h"

VerticalAlignment::VerticalAlignment(uint8_t value) {
    this->alignment = value;
}

VerticalAlignment::VerticalAlignment(void) {
    this->alignment = 1;
}

VerticalAlignment::VerticalAlignment(const VerticalAlignment &value) {
    this->alignment = value.alignment;
}

void VerticalAlignment::operator=(const VerticalAlignment &value) {
    this->alignment = value.alignment;
}

bool VerticalAlignment::operator==(const VerticalAlignment &another) const {
    return this->alignment == another.alignment;
}

bool VerticalAlignment::operator!=(const VerticalAlignment &another) const {
    return this->alignment != another.alignment;
}

HorizontalAlignment::HorizontalAlignment(uint8_t value) {
    this->alignment = value;
}

HorizontalAlignment::HorizontalAlignment(void) {
    this->alignment = 1;
}

HorizontalAlignment::HorizontalAlignment(const HorizontalAlignment &value) {
    this->alignment = value.alignment;
}

void HorizontalAlignment::operator=(const HorizontalAlignment &value) {
    this->alignment = value.alignment;
}

bool HorizontalAlignment::operator==(const HorizontalAlignment &another) const {
    return this->alignment == another.alignment;
}

bool HorizontalAlignment::operator!=(const HorizontalAlignment &another) const {
    return this->alignment != another.alignment;
}

const VerticalAlignment VerticalAlignment::Top = 0;
const VerticalAlignment VerticalAlignment::Center = 1;
const VerticalAlignment VerticalAlignment::Bottom = 2;

const HorizontalAlignment HorizontalAlignment::Left = 0;
const HorizontalAlignment HorizontalAlignment::Center = 1;
const HorizontalAlignment HorizontalAlignment::Right = 2;
