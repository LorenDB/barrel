#ifndef CONTINUESTATEMENT_H
#define CONTINUESTATEMENT_H

#include "InstructionNode.h"

class ContinueStatement : public InstructionNode
{
    Q_OBJECT

public:
    ContinueStatement(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // CONTINUESTATEMENT_H
