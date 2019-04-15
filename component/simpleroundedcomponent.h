#ifndef SIMPLEROUNDEDCOMPONENT_H
#define SIMPLEROUNDEDCOMPONENT_H
#include"component.h"

class SimpleRoundedComponent : public Component
{
public:
    SimpleRoundedComponent(size_t _w, size_t _h);

private:
    size_t w;
    size_t h;

};

#endif // SIMPLEROUNDEDCOMPONENT_H
