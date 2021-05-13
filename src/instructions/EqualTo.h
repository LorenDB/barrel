#ifndef EQUALTO_H
#define EQUALTO_H

#include "EqualityOperation.h"

class EqualTo : public EqualityOperation
{
    Q_OBJECT

public:
    EqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec() override;
};

#endif // EQUALTO_H
