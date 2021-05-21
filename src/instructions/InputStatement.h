#ifndef INPUTSTATEMENT_H
#define INPUTSTATEMENT_H

#include "InstructionNode.h"

class InputStatement : public InstructionNode
{
    Q_OBJECT

public:
    InputStatement(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // INPUTSTATEMENT_H
