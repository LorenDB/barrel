#ifndef DIVIDESTATEMENT_H
#define DIVIDESTATEMENT_H

#include "InstructionNode.h"

class DivideStatement : public InstructionNode
{
    Q_OBJECT

public:
    DivideStatement(InstructionNode *divisor, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_divisor;
};

#endif // DIVIDESTATEMENT_H
