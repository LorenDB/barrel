#include "GreaterThanEqualTo.h"

GreaterThanEqualTo::GreaterThanEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant GreaterThanEqualTo::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {m_parser->accumulator() >= value.toDouble()};
}
