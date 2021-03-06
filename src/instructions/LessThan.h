#ifndef LESSTHAN_H
#define LESSTHAN_H

#include "EqualityOperation.h"

class LessThan : public EqualityOperation
{
    Q_OBJECT

public:
    LessThan(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // LESSTHAN_H
