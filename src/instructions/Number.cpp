#include "Number.h"

Number::Number(double value, BarrelParser &parser) : InstructionNode{parser}, m_value{value} {}

QVariant Number::exec()
{
    return {m_value};
}
