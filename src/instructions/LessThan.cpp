#include "LessThan.h"

LessThan::LessThan(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant LessThan::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {m_parser->accumulator() < value.toDouble()};
}
