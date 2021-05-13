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
