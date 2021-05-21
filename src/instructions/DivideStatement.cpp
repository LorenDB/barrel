#include "DivideStatement.h"

DivideStatement::DivideStatement(InstructionNode *divisor, BarrelParser &parser)
    : InstructionNode{parser},
      m_divisor{divisor}
{
}

DivideStatement::~DivideStatement()
{
    delete m_divisor;
}

QVariant DivideStatement::exec(ExecRole role)
{
    m_parser->setAccumulator(m_parser->accumulator() / m_divisor->exec(NumericalValue).toDouble());
    return {m_parser->accumulator()};
}

bool DivideStatement::hasAsChild(InstructionNode *other)
{
    if (m_divisor == other || m_divisor->hasAsChild(other))
        return true;

    return false;
}
