#include "FuzzyNotEqualTo.h"

FuzzyNotEqualTo::FuzzyNotEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant FuzzyNotEqualTo::exec()
{
    auto value = m_valueToCompareTo->exec();
    if (value.isValid())
        return {!(abs(m_parser->accumulator() - value.toDouble()) <
                  m_parser->controlRegisterAt(BarrelParser::FUZZY_COMPARE_REG))};
    else
        return {}; // CRASHANDBURNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
