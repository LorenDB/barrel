#ifndef SQUAREROOTACC_H
#define SQUAREROOTACC_H

#include "InstructionNode.h"

class SquareRootAcc : public InstructionNode
{
    Q_OBJECT

public:
    SquareRootAcc(BarrelParser &parser);

    QVariant exec() override;
};

#endif // SQUAREROOTACC_H
