#ifndef STACKACCESSOR_H
#define STACKACCESSOR_H

#include "InstructionNode.h"

class StackAccessor : public InstructionNode
{
    Q_OBJECT

public:
    StackAccessor(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // STACKACCESSOR_H
