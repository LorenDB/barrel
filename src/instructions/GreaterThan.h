#ifndef GREATERTHAN_H
#define GREATERTHAN_H

#include "EqualityOperation.h"

class GreaterThan : public EqualityOperation
{
    Q_OBJECT

public:
    GreaterThan(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec() override;
};

#endif // GREATERTHAN_H
