#include "GreaterThanEqualTo.h"

GreaterThanEqualTo::GreaterThanEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant GreaterThanEqualTo::exec()
{
    auto value = m_valueToCompareTo->exec();
    if (value.isValid())
        return {m_parser->accumulator() >= value.toDouble()};
    else
        return {}; // CRASHANDBURNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
