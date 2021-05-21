#include "Number.h"

Number::Number(double value, BarrelParser &parser) : InstructionNode{parser}, m_value{value} {}

QVariant Number::exec(ExecRole role)
{
    if (role != NumericalValue)
        m_parser->print(m_value);

    return {m_value};
}
