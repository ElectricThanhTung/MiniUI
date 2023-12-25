
#include "miniui_control.h"
#include "miniui_collections.h"

Control::Control(const Size &size) : actualSize(Size::None), size(size) {
    this->parent = 0;
    this->parentList = 0;
    this->prev = 0;
    this->next = 0;
    this->SetVisible(true);
    this->SetVerticalAlignment(VerticalAlignment::Center);
    this->SetHorizontalAlignment(HorizontalAlignment::Center);
}

const char *Control::GetType(void) {
    return "Control";
}

void Control::RequestUpdate(void) {
    if(this->parent)
        this->parent->RequestUpdate();
}

bool Control::operator==(Control &another) {
    return this == &another;
}

bool Control::operator!=(Control &another) {
    return this != &another;
}

void Control::SetParent(Control &parent) {
    this->parent = &parent;
}

Control &Control::GetParent(void) const {
    return *this->parent;
}

void Control::SetParentList(void *parentList) {
    this->parentList = parentList;
}

void *Control::GetParentList(void) const {
    return this->parentList;
}

void Control::SetPrev(Control &prev) {
    this->prev = &prev;
}

Control &Control::GetPrev(void) const {
    return *this->prev;
}

void Control::SetNext(Control &next) {
    this->next = &next;
}

Control &Control::GetNext(void) const {
    return *this->next;
}

void Control::SetActualWidth(int16_t value) {
    *(int16_t *)&this->actualSize.Width = value;
}

void Control::SetActualHeight(int16_t value) {
    *(int16_t *)&this->actualSize.Height = value;
}

const Size &Control::GetActualSize(void) const {
    return this->actualSize;
}

void Control::SetSize(const Size &size) {
    this->size = size;
}

void Control::SetSize(int16_t width, int16_t height) {
    this->size = Size(width, height);
}

void Control::SetWidth(int16_t width) {
    *(int16_t *)&this->size.Width = width;
}

void Control::SetHeight(int16_t height) {
    *(int16_t *)&this->size.Height = height;
}

const Size &Control::GetSize(void) const {
    return this->size;
}

void Control::SetMargin(const Thickness &margin) {
    this->margin = margin;
}

void Control::SetMargin(int16_t uniformSize) {
    this->margin = Thickness(uniformSize);
}

void Control::SetMargin(int16_t left, int16_t top, int16_t right, int16_t bottom) {
    this->margin = Thickness(left, top, right, bottom);
}

void Control::SetMarginLeft(int16_t left) {
    *(int16_t *)&this->margin.Left = left;
}

void Control::SetMarginTop(int16_t top) {
    *(int16_t *)&this->margin.Top = top;
}

void Control::SetMarginRight(int16_t right) {
    *(int16_t *)&this->margin.Right = right;
}

void Control::SetMarginBottom(int16_t bottom) {
    *(int16_t *)&this->margin.Bottom = bottom;
}

const Thickness &Control::GetMargin(void) const {
    return this->margin;
}

void Control::SetVisible(bool visible) {
    this->visible = visible ? 1 : 0;
}

bool Control::GetVisible(void) const {
    return this->visible == 1;
}

void Control::SetVerticalAlignment(const VerticalAlignment &alignment) {
    this->verticalAlignment = *(uint8_t *)&alignment;
}

VerticalAlignment Control::GetVerticalAlignment(void) const {
    uint8_t temp = this->verticalAlignment;
    return *(VerticalAlignment *)&temp;
}

void Control::SetHorizontalAlignment(const HorizontalAlignment &alignment) {
    this->horizontalAlignment = *(uint8_t *)&alignment;
}

HorizontalAlignment Control::GetHorizontalAlignment(void) const {
    uint8_t temp = this->horizontalAlignment;
    return *(HorizontalAlignment *)&temp;
}

Control::~Control(void) {
    Collections *objParentList = (Collections *)this->parentList;
    if(objParentList)
        objParentList->Remove(*this);
    this->parent = &NULL_CONTROL;
}
