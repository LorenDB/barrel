#include "EqualityOperation.h"

EqualityOperation::EqualityOperation(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : InstructionNode{parser},
      m_valueToCompareTo{valueToCompareTo}
{
}
