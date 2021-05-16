#ifndef LOOP_H
#define LOOP_H

#include "InstructionNode.h"

class Loop : public InstructionNode
{
    Q_OBJECT

public:
    Loop(InstructionNode *times, InstructionNode *body, BarrelParser &parser);

    QVariant exec() override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_times;
    InstructionNode *m_body;
};

#endif // LOOP_H
