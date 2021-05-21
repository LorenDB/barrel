#include "NotEqualTo.h"

NotEqualTo::NotEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant NotEqualTo::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {m_parser->accumulator() != value.toDouble()};
}

bool NotEqualTo::hasAsChild(InstructionNode *other)
{
    if (m_valueToCompareTo == other || m_valueToCompareTo->hasAsChild(other))
        return true;

    return false;
}
