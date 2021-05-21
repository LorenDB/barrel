#ifndef PUSHLOCATIONPOINTER_H
#define PUSHLOCATIONPOINTER_H

#include "InstructionNode.h"

class PushLocationPointer : public InstructionNode
{
    Q_OBJECT

public:
    PushLocationPointer(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // PUSHLOCATIONPOINTER_H
