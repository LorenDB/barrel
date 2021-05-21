#ifndef ACCUMULATORACCESSOR_H
#define ACCUMULATORACCESSOR_H

#include "InstructionNode.h"

class AccumulatorAccessor : public InstructionNode
{
    Q_OBJECT

public:
    AccumulatorAccessor(BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
};

#endif // ACCUMULATORACCESSOR_H
