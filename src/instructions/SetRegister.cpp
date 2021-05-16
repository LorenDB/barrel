#include "SetRegister.h"

SetRegister::SetRegister(InstructionNode *index, InstructionNode *value, BarrelParser &parser)
    : InstructionNode{parser},
      m_index{index},
      m_value{value}
{
}

QVariant SetRegister::exec()
{
    m_parser->setRegisterAt(m_index->exec().toInt(), m_value->exec().toDouble());
    return {};
}

bool SetRegister::hasAsChild(InstructionNode *other)
{
    if (m_index == other || m_value == other || m_index->hasAsChild(other) || m_value->hasAsChild(other))
        return true;

    return false;
}
