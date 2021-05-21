#include "FuzzyNotEqualTo.h"

FuzzyNotEqualTo::FuzzyNotEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser)
    : EqualityOperation{valueToCompareTo, parser}
{
}

QVariant FuzzyNotEqualTo::exec(ExecRole role)
{
    auto value = m_valueToCompareTo->exec(NumericalValue);

    return {!(abs(m_parser->accumulator() - value.toDouble()) <
              m_parser->controlRegisterAt(BarrelParser::FUZZY_COMPARE_REG))};
}
