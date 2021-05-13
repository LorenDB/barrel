#include "BarrelString.h"

BarrelString::BarrelString(const QString &string, BarrelParser &parser)
    : InstructionNode{parser},
      m_string{string}
{
}

QVariant BarrelString::exec()
{
    m_parser->print(m_string);
    return {m_string};
}
