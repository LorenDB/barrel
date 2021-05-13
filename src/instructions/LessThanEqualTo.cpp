#include "LessThanEqualTo.h"

LessThanEqualTo::LessThanEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant LessThanEqualTo::exec()
{
    auto value = m_valueToCompareTo->exec();
    if (value.isValid())
        return {m_parser->accumulator() <= value.toDouble()};
    else
        return {}; // CRASHANDBURNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
