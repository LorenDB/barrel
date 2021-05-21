#ifndef FUZZYEQUALTO_H
#define FUZZYEQUALTO_H

#include "EqualityOperation.h"

class FuzzyEqualTo : public EqualityOperation
{
    Q_OBJECT

public:
    FuzzyEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // FUZZYEQUALTO_H
