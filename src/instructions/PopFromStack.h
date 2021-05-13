#ifndef POPFROMSTACK_H
#define POPFROMSTACK_H

#include "InstructionNode.h"

class PopFromStack : public InstructionNode
{
    Q_OBJECT

public:
    PopFromStack(BarrelParser &parser);

    QVariant exec() override;
};

#endif // POPFROMSTACK_H
