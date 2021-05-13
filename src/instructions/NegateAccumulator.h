#ifndef NEGATEACCUMULATOR_H
#define NEGATEACCUMULATOR_H

#include "InstructionNode.h"

class NegateAccumulator : public InstructionNode
{
    Q_OBJECT

public:
    NegateAccumulator(BarrelParser &parser);

    QVariant exec() override;
};

#endif // NEGATEACCUMULATOR_H
