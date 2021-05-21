#include "SetRegister.h"

SetRegister::SetRegister(InstructionNode *index, InstructionNode *value, BarrelParser &parser)
    : InstructionNode{parser},
      m_index{index},
      m_value{value}
{
}

QVariant SetRegister::exec(ExecRole role)
{
    auto reg = m_index->exec(NumericalValue).toInt();
    m_parser->setRegisterAt(reg, m_value->exec(NumericalValue).toDouble());
    return {m_parser->registerAt(reg)};
}

bool SetRegister::hasAsChild(InstructionNode *other)
{
    if (m_index == other || m_value == other || m_index->hasAsChild(other) || m_value->hasAsChild(other))
        return true;

    return false;
}
