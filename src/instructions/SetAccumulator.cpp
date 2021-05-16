#include "SetAccumulator.h"

SetAccumulator::SetAccumulator(InstructionNode *newValue, BarrelParser &parser)
    : InstructionNode{parser},
      m_newValue{newValue}
{
}

QVariant SetAccumulator::exec()
{
    auto value = m_newValue->exec();
    if (value.isValid())
        m_parser->setAccumulator(value.toDouble());
    else
        ; // TODO: DO A CRASH AND BURN

    return {};
}

bool SetAccumulator::hasAsChild(InstructionNode *other)
{
    if (m_newValue == other || m_newValue->hasAsChild(other))
        return true;

    return false;
}
