#ifndef PRIMALITYTEST_H
#define PRIMALITYTEST_H

#include "InstructionNode.h"

class PrimalityTest : public InstructionNode
{
    Q_OBJECT

public:
    PrimalityTest(InstructionNode *numberToTest, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;

private:
    InstructionNode *m_numberToTest;
};

#endif // PRIMALITYTEST_H
