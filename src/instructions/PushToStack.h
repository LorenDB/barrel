#ifndef PUSHTOSTACK_H
#define PUSHTOSTACK_H

#include "InstructionNode.h"

class PushToStack : public InstructionNode
{
    Q_OBJECT

public:
    PushToStack(InstructionNode *numToPush, BarrelParser &parser);
    ~PushToStack();

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_numToPush;
};

#endif // PUSHTOSTACK_H
