#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include "InstructionNode.h"

class RandomNumberGenerator : public InstructionNode
{
    Q_OBJECT

public:
    RandomNumberGenerator(BarrelParser &parser);

    QVariant exec() override;
};

#endif // RANDOMNUMBERGENERATOR_H
