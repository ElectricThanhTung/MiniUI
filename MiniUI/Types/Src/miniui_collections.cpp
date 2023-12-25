
#include "miniui_collections.h"

Collections::Collections(Control &parent) : Count(0) {
    this->Parent = &parent;
    this->End = 0;
    this->Current = 0;
    this->Index = 0;
}

void Collections::Add(Control &obj) {
    Collections *objParentList = (Collections *)obj.GetParentList();
    if((objParentList != this) && (obj != *this->Parent)) {
        if(objParentList)
            objParentList->Remove(obj);

        if(!this->End) {
            obj.SetPrev(obj);
            obj.SetNext(obj);
            this->End = &obj;
        }
        else {
            obj.SetPrev(*this->End);
            obj.SetNext(this->End->GetNext());

            obj.GetPrev().SetNext(obj);
            obj.GetNext().SetPrev(obj);

            this->End = &obj;
        }

        obj.SetParentList(this);
        obj.SetParent(*this->Parent);

        (*(uint16_t *)&this->Count)++;
        this->Index = 0;
        this->Current = &this->End->GetNext();
    }
    else
        throw "Object already exists in this collections or it's parents of this collections";
}

void Collections::Remove(Control &obj) {
    Collections *objParentList = (Collections *)obj.GetParentList();
    if(objParentList == this) {
        if(obj == *this->End)
            this->End = (*this->End == obj.GetPrev()) ? &NULL_CONTROL : &obj.GetPrev();

        obj.GetPrev().SetNext(obj.GetNext());
        obj.GetNext().SetPrev(obj.GetPrev());

        obj.SetPrev(NULL_CONTROL);
        obj.SetNext(NULL_CONTROL);
        obj.SetParentList(0);
        obj.SetParent(NULL_CONTROL);

        (*(uint16_t *)&this->Count)--;
        this->Index = 0;
        this->Current = this->End ? &this->End->GetNext() : &NULL_CONTROL;
    }
}

void Collections::RemoveAt(uint16_t index) {
    this->Remove((*this)[index]);
}

Control &Collections::operator[](uint16_t index) {
    if(index < this->Count) {
        if((index - 0) < (this->Index - index)) {
            this->Index = 0;
            this->Current = &this->End->GetNext();
        }
        if(this->Index <= index) {
            while(this->Index < index) {
                this->Current = &this->Current->GetNext();
                this->Index++;
            }
        }
        else {
            while(this->Index > index) {
                this->Current = &this->Current->GetPrev();
                this->Index--;
            }
        }
        return *this->Current;
    }
    throw "Index out of range";
}
