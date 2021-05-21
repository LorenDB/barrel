#ifndef EXITSTATEMENT_H
#define EXITSTATEMENT_H

#include "InstructionNode.h"

class ExitStatement : public InstructionNode
{
    Q_OBJECT

public:
    ExitStatement(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // EXITSTATEMENT_H
