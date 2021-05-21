#include "RegisterAccessor.h"

RegisterAccessor::RegisterAccessor(InstructionNode *index, BarrelParser &parser)
    : InstructionNode{parser},
      m_index{index}
{
}

RegisterAccessor::~RegisterAccessor()
{
    delete m_index;
}

QVariant RegisterAccessor::exec(ExecRole role)
{
    return {m_parser->registerAt(m_index->exec(NumericalValue).toInt())};
}

bool RegisterAccessor::hasAsChild(InstructionNode *other)
{
    if (m_index == other || m_index->hasAsChild(other))
        return true;

    return false;
}
