#ifndef LESSTHANEQUALTO_H
#define LESSTHANEQUALTO_H

#include "EqualityOperation.h"

class LessThanEqualTo : public EqualityOperation
{
    Q_OBJECT

public:
    LessThanEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec() override;
};

#endif // LESSTHANEQUALTO_H
