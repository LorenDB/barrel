#ifndef INFINITY_H
#define INFINITY_H

#include "Number.h"

class Infinity : public Number
{
    Q_OBJECT

public:
    Infinity(BarrelParser &parser);
};

#endif // INFINITY_H
