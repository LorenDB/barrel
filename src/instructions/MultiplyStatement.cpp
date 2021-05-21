#include "MultiplyStatement.h"

MultiplyStatement::MultiplyStatement(InstructionNode *factor, BarrelParser &parser)
    : InstructionNode{parser},
      m_factor{factor}
{
}

QVariant MultiplyStatement::exec(ExecRole role)
{
    m_parser->setAccumulator(m_parser->accumulator() * m_factor->exec(NumericalValue).toDouble());
    return {m_parser->accumulator()};
}

bool MultiplyStatement::hasAsChild(InstructionNode *other)
{
    if (m_factor == other || m_factor->hasAsChild(other))
        return true;

    return false;
}
