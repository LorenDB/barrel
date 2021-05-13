#include "LessThan.h"

LessThan::LessThan(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant LessThan::exec()
{
    auto value = m_valueToCompareTo->exec();
    if (value.isValid())
        return {m_parser->accumulator() < value.toDouble()};
    else
        return {}; // CRASHANDBURNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
