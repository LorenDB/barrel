#include "EqualTo.h"

EqualTo::EqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant EqualTo::exec()
{
    auto value = m_valueToCompareTo->exec();
    if (value.isValid())
        return {m_parser->accumulator() == value.toDouble()};
    else
        return {}; // CRASHANDBURNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
