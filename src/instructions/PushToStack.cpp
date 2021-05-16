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

bool PushToStack::hasAsChild(InstructionNode *other)
{
    if (m_numToPush == other || m_numToPush->hasAsChild(other))
        return true;

    return false;
}
