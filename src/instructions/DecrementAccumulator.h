#ifndef DECREMENTACCUMULATOR_H
#define DECREMENTACCUMULATOR_H

#include "InstructionNode.h"

class DecrementAccumulator : public InstructionNode
{
    Q_OBJECT

public:
    DecrementAccumulator(BarrelParser &parser);

    QVariant exec() override;
};

#endif // DECREMENTACCUMULATOR_H
