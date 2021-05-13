#ifndef REGISTERACCESSOR_H
#define REGISTERACCESSOR_H

#include "InstructionNode.h"

class RegisterAccessor : public InstructionNode
{
    Q_OBJECT

public:
    RegisterAccessor(InstructionNode *index, BarrelParser &parser);

    QVariant exec() override;

private:
    InstructionNode *m_index;
};

#endif // REGISTERACCESSOR_H
