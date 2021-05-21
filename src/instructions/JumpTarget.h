#ifndef JUMPTARGET_H
#define JUMPTARGET_H

#include "InstructionNode.h"

class JumpTarget : public InstructionNode
{
    Q_OBJECT

public:
    JumpTarget(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // JUMPTARGET_H
