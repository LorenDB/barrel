#ifndef MULTIPLYSTATEMENT_H
#define MULTIPLYSTATEMENT_H

#include "InstructionNode.h"

class MultiplyStatement : public InstructionNode
{
    Q_OBJECT

public:
    MultiplyStatement(InstructionNode *factor, BarrelParser &parser);
    ~MultiplyStatement();

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_factor;
};

#endif // MULTIPLYSTATEMENT_H
