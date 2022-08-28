
#ifndef __COLLECTIONS_HPP
#define __COLLECTIONS_HPP

#include "UI.hpp"

#define MAX_OF_COLLECTIONS          50

class Collections {
public:
    Collections(UI *objContext);

    void Add(UI &obj);
    void AddRange(Collections &objs);

    void Remove(UI &obj);
    void RemoveAt(unsigned short index);

    UI *operator[](unsigned short index);

    unsigned short Count();
private:
    UI *objs[MAX_OF_COLLECTIONS] = {0};
    UI *const ObjectContext;
    unsigned short count = 0;

    void SetParent(UI &obj, UI &parent);
};

#endif // __COLLECTIONS_HPP
