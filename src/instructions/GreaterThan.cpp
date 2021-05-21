#include "GreaterThan.h"

GreaterThan::GreaterThan(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant GreaterThan::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {m_parser->accumulator() > value.toDouble()};
}
