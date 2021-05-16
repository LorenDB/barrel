#ifndef EQUALITYOPERATION_H
#define EQUALITYOPERATION_H

#include "InstructionNode.h"

class EqualityOperation : public InstructionNode
{
    Q_OBJECT

public:
    EqualityOperation(InstructionNode *valueToCompareTo, BarrelParser &parser);

    bool hasAsChild(InstructionNode *other) override;

protected:
    InstructionNode *m_valueToCompareTo;
};

#endif // EQUALITYOPERATION_H
