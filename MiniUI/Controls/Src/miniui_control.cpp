
#include "miniui_control.h"
#include "miniui_collections.h"

Control::Control(const Size &size) : actualRect(Point(0, 0), Size::NoneSize), size(size) {
    this->parent = 0;
    this->parentList = 0;
    this->prev = 0;
    this->next = 0;
    this->visible = true;
}

void Control::SetRequestRect(const Rect &rect) {

}

bool Control::RequestUpdate(bool isRecall) {
    if(this->parent) {
        const Rect oldRect = this->actualRect;
        if(this->parent->RequestUpdate(true) == false) {
            if(oldRect != this->actualRect) {
                this->GetTopParent().SetRequestRect(this->parent->actualRect);
                return true;
            }
            else if(isRecall)
                return false;
            else
                this->GetTopParent().SetRequestRect(oldRect);
        }
    }
    return true;
}

bool Control::operator==(Control &another) {
    return this == &another;
}

bool Control::operator!=(Control &another) {
    return this != &another;
}

void Control::SetParent(Control &parent) {
    if(this->parent != &parent) {
        this->parent = &parent;
        this->RequestUpdate();
    }
}

Control &Control::GetParent(void) {
    return *this->parent;
}

Control &Control::GetTopParent(void) {
    Control *ret = this->parent;
    while(ret->parent)
        ret = ret->parent;
    return *ret;
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
    *(int16_t *)&this->actualRect.Width = value;
}

void Control::SetActualHeight(int16_t value) {
    *(int16_t *)&this->actualRect.Height = value;
}

void Control::SetLocation(int16_t x, int16_t y) {
    *(int16_t *)&this->actualRect.Left = x;
    *(int16_t *)&this->actualRect.Top = y;
}

const Point &Control::GetLoaction(void) {
    return this->actualRect.Location;
}

const Size &Control::GetActualSize(void) {
    return this->actualRect.Size;
}

void Control::SetSize(const Size &size) {
    if( this->size != size) {
        this->size = size;
        this->RequestUpdate();
    }
}

const Size &Control::GetSize(void) {
    return this->size;
}

void Control::SetMargin(const Thickness &margin) {
    if(this->margin != margin) {
        this->margin = margin;
        this->RequestUpdate();
    }
}

const Thickness &Control::GetMargin(void) {
    return this->margin;
}

void Control::SetVisible(bool visible) {
    if(this->visible != visible) {
        this->visible = visible;
        this->RequestUpdate();
    }
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
