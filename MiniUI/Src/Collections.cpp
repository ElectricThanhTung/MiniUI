
#include "Collections.hpp"

Collections::Collections(UI *objContext) : ObjectContext(objContext) {

}

void Collections::Add(UI &obj) {
    if(obj.Parent == 0) {
        this->objs[count] = &obj;
        this->SetParent(obj, *this->ObjectContext);
        this->count++;
    }
}

void Collections::AddRange(Collections &list) {
    for(unsigned short i = 0; i < list.count; i++) {
        if(!list[i]->Parent == 0) {
            this->objs[this->count + i] = list[i];
            this->SetParent(*list[i], *this->ObjectContext);
            this->count++;
        }
    }
}

void Collections::Remove(UI &obj) {
    for(unsigned short i = 0; i < this->count; i++) {
        if(objs[i] == &obj) {
            this->RemoveAt(i);
            break;
        }
    }
}

void Collections::RemoveAt(unsigned short index) {
    this->SetParent(*this->objs[index], *(UI *)0);
    for(unsigned short i = index; i < (this->count - 1); i++)
        this->objs[i] = this->objs[i + 1];
    this->objs[this->count - 1] = 0;
    this->count--;
}

unsigned short Collections::Count() {
    return this->count;
}

UI *Collections::operator[](unsigned short index) {
    return this->objs[index];
}

void Collections::SetParent(UI &obj, UI &parent) {
    *(UI **)&obj.Parent = &parent;
}
