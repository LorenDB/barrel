#include "LessThanEqualTo.h"

LessThanEqualTo::LessThanEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant LessThanEqualTo::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {m_parser->accumulator() <= value.toDouble()};
}
