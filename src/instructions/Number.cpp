#include "Number.h"

Number::Number(double value, BarrelParser &parser) : InstructionNode{parser}, m_value{value} {}

QVariant Number::exec(ExecRole role)
{
    return {m_value};
}
