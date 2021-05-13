#ifndef INCREMENTACCUMULATOR_H
#define INCREMENTACCUMULATOR_H

#include "InstructionNode.h"

class IncrementAccumulator : public InstructionNode
{
    Q_OBJECT

public:
    IncrementAccumulator(BarrelParser &parser);

    QVariant exec() override;
};

#endif // INCREMENTACCUMULATOR_H
