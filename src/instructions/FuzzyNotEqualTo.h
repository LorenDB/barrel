#ifndef FUZZYNOTEQUALTO_H
#define FUZZYNOTEQUALTO_H

#include "EqualityOperation.h"

class FuzzyNotEqualTo : public EqualityOperation
{
    Q_OBJECT

public:
    FuzzyNotEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // FUZZYNOTEQUALTO_H
