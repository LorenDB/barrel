#include "RegisterAccessor.h"

RegisterAccessor::RegisterAccessor(InstructionNode *index, BarrelParser &parser)
    : InstructionNode{parser},
      m_index{index}
{
}

QVariant RegisterAccessor::exec()
{
    return {m_parser->registerAt(m_index->exec().toInt())};
}
