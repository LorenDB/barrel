#ifndef POPLOCATIONPOINTER_H
#define POPLOCATIONPOINTER_H

#include "InstructionNode.h"

class PopLocationPointer : public InstructionNode
{
    Q_OBJECT

public:
    PopLocationPointer(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // POPLOCATIONPOINTER_H
