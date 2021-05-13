#ifndef RECIPROCATEACCUMULATOR_H
#define RECIPROCATEACCUMULATOR_H

#include "InstructionNode.h"

class ReciprocateAccumulator : public InstructionNode
{
    Q_OBJECT
public:
    ReciprocateAccumulator(BarrelParser &parser);

    QVariant exec() override;
};

#endif // RECIPROCATEACCUMULATOR_H
