#include "PushToStack.h"

PushToStack::PushToStack(InstructionNode *numToPush, BarrelParser &parser)
    : InstructionNode{parser},
      m_numToPush{numToPush}
{
}

QVariant PushToStack::exec()
{
    m_parser->pushToStack(m_numToPush->exec().toDouble());
    return {};
}
