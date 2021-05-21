#include "BarrelString.h"

BarrelString::BarrelString(const QString &string, BarrelParser &parser)
    : InstructionNode{parser},
      m_string{string}
{
}

QVariant BarrelString::exec(ExecRole role)
{
    m_parser->print(m_string);
    if (role == NumericalValue)
        return {static_cast<int>(m_string[0].toLatin1())};

    return {m_string};
}
