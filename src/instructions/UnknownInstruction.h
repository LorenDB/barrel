#ifndef UNKNOWNINSTRUCTION_H
#define UNKNOWNINSTRUCTION_H

#include "InstructionNode.h"

class UnknownInstruction : public InstructionNode
{
    Q_OBJECT

public:
    UnknownInstruction(QChar instruction, BarrelParser &parser);

    QVariant exec(ExecRole role) override;

private:
    QChar m_instruction;
};

#endif // UNKNOWNINSTRUCTION_H
