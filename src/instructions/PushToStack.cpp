#include "PushToStack.h"

PushToStack::PushToStack(InstructionNode *numToPush, BarrelParser &parser)
    : InstructionNode{parser},
      m_numToPush{numToPush}
{
}

PushToStack::~PushToStack()
{
    delete m_numToPush;
}

QVariant PushToStack::exec(ExecRole role)
{
    m_parser->pushToStack(m_numToPush->exec(NumericalValue).toDouble());
    return {m_parser->topOfStack()};
}

bool PushToStack::hasAsChild(InstructionNode *other)
{
    if (m_numToPush == other || m_numToPush->hasAsChild(other))
        return true;

    return false;
}
