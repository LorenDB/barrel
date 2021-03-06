#include "EqualityOperation.h"

EqualityOperation::EqualityOperation(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : InstructionNode{parser},
      m_valueToCompareTo{valueToCompareTo}
{
}

EqualityOperation::~EqualityOperation()
{
    delete m_valueToCompareTo;
}

bool EqualityOperation::hasAsChild(InstructionNode *other)
{
    if (m_valueToCompareTo == other || m_valueToCompareTo->hasAsChild(other))
        return true;

    return false;
}
