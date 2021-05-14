#include "DivideStatement.h"

DivideStatement::DivideStatement(InstructionNode *divisor, BarrelParser &parser)
    : InstructionNode{parser},
      m_divisor{divisor}
{
}

QVariant DivideStatement::exec()
{
    m_parser->setAccumulator(m_parser->accumulator() / m_divisor->exec().toDouble());
    return {m_parser->accumulator()};
}
