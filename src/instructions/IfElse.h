#ifndef IFELSE_H
#define IFELSE_H

#include "InstructionChain.h"
#include "InstructionNode.h"

class IfElse : public InstructionNode
{
    Q_OBJECT

public:
    explicit IfElse(InstructionNode *evalNode, InstructionNode *truthyNode,
                    InstructionNode *falseyNode, BarrelParser &parser);

    QVariant exec() override;
    bool hasAsChild(InstructionNode *other) override;

signals:

private:
    InstructionNode *m_evalNode = nullptr;
    InstructionNode *m_truthyNode = nullptr;
    InstructionNode *m_falseyNode = nullptr;
};

#endif // IFELSE_H
