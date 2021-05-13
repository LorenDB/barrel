#include "NotEqualTo.h"

NotEqualTo::NotEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant NotEqualTo::exec()
{
    auto value = m_valueToCompareTo->exec();
    if (value.isValid())
        return {m_parser->accumulator() != value.toDouble()};
    else
        return {}; // CRASHANDBURNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
