
#include "miniui_control.h"
#include "miniui_collections.h"

Control::Control(const Size &size) : actualSize(Size::NoneSize), size(size) {
    this->parent = 0;
    this->parentList = 0;
    this->prev = 0;
    this->next = 0;
    this->visible = true;
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

Control &Control::GetParent(void) {
    return *this->parent;
}

void Control::SetParentList(void *parentList) {
    this->parentList = parentList;
}

void *Control::GetParentList(void) {
    return this->parentList;
}

void Control::SetPrev(Control &prev) {
    this->prev = &prev;
}

Control &Control::GetPrev(void) {
    return *this->prev;
}

void Control::SetNext(Control &next) {
    this->next = &next;
}

Control &Control::GetNext(void) {
    return *this->next;
}

void Control::SetActualWidth(int16_t value) {
    *(int16_t *)&this->actualSize.Width = value;
}

void Control::SetActualHeight(int16_t value) {
    *(int16_t *)&this->actualSize.Height = value;
}

const Size &Control::GetActualSize(void) {
    return this->actualSize;
}

void Control::SetSize(const Size &size) {
    this->size = size;
}

const Size &Control::GetSize(void) {
    return this->size;
}

void Control::SetMargin(const Thickness &margin) {
    this->margin = margin;
}

const Thickness &Control::GetMargin(void) {
    return this->margin;
}

void Control::SetVisible(bool visible) {
    this->visible = visible;
}

bool Control::GetVisible(void) {
    return this->visible;
}

Control::~Control(void) {
    Collections *objParentList = (Collections *)this->parentList;
    if(objParentList)
        objParentList->Remove(*this);
    this->parent = &NULL_CONTROL;
}
