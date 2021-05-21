#ifndef SQUAREROOTACC_H
#define SQUAREROOTACC_H

#include "InstructionNode.h"

class SquareRootAcc : public InstructionNode
{
    Q_OBJECT

public:
    SquareRootAcc(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // SQUAREROOTACC_H
