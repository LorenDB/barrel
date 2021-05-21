#ifndef SETACCUMULATOR_H
#define SETACCUMULATOR_H

#include "InstructionNode.h"

class SetAccumulator : public InstructionNode
{
    Q_OBJECT

public:
    SetAccumulator(InstructionNode *newValue, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_newValue;
};

#endif // SETACCUMULATOR_H
