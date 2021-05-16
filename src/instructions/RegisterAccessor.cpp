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

bool RegisterAccessor::hasAsChild(InstructionNode *other)
{
    if (m_index == other || m_index->hasAsChild(other))
        return true;

    return false;
}
