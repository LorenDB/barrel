#include "SetAccumulator.h"

SetAccumulator::SetAccumulator(InstructionNode *newValue, BarrelParser &parser)
    : InstructionNode{parser},
      m_newValue{newValue}
{
}

QVariant SetAccumulator::exec(ExecRole role)
{
    auto value = m_newValue->exec(NumericalValue);
    m_parser->setAccumulator(value.toDouble());

    return {value};
}

bool SetAccumulator::hasAsChild(InstructionNode *other)
{
    if (m_newValue == other || m_newValue->hasAsChild(other))
        return true;

    return false;
}
