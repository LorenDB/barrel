#ifndef POPLOCATIONPOINTER_H
#define POPLOCATIONPOINTER_H

#include "InstructionNode.h"

class PopLocationPointer : public InstructionNode
{
    Q_OBJECT

public:
    PopLocationPointer(BarrelParser &parser);

    QVariant exec() override;
};

#endif // POPLOCATIONPOINTER_H
