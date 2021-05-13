#ifndef PUSHLOCATIONPOINTER_H
#define PUSHLOCATIONPOINTER_H

#include "InstructionNode.h"

class PushLocationPointer : public InstructionNode
{
    Q_OBJECT

public:
    PushLocationPointer(BarrelParser &parser);

    QVariant exec() override;
};

#endif // PUSHLOCATIONPOINTER_H
