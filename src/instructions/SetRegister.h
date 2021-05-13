#ifndef SETREGISTER_H
#define SETREGISTER_H

#include "InstructionNode.h"

class SetRegister : public InstructionNode
{
    Q_OBJECT
public:
    SetRegister(InstructionNode *index, InstructionNode *value, BarrelParser &parser);

    QVariant exec() override;

private:
    InstructionNode *m_index;
    InstructionNode *m_value;
};

#endif // SETREGISTER_H
