#ifndef GREATERTHANEQUALTO_H
#define GREATERTHANEQUALTO_H

#include "EqualityOperation.h"

class GreaterThanEqualTo : public EqualityOperation
{
    Q_OBJECT

public:
    GreaterThanEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec() override;
};

#endif // GREATERTHANEQUALTO_H
