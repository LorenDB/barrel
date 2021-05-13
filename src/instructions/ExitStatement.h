#ifndef EXITSTATEMENT_H
#define EXITSTATEMENT_H

#include "InstructionNode.h"

class ExitStatement : public InstructionNode
{
    Q_OBJECT

public:
    ExitStatement(BarrelParser &parser);

    QVariant exec() override;
};

#endif // EXITSTATEMENT_H
