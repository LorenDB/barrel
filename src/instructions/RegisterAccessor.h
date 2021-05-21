#ifndef REGISTERACCESSOR_H
#define REGISTERACCESSOR_H

#include "InstructionNode.h"

class RegisterAccessor : public InstructionNode
{
    Q_OBJECT

public:
    RegisterAccessor(InstructionNode *index, BarrelParser &parser);
    ~RegisterAccessor();

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_index;
};

#endif // REGISTERACCESSOR_H
