#include "EqualTo.h"

EqualTo::EqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant EqualTo::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {m_parser->accumulator() == value.toDouble()};
}
