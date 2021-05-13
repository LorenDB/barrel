#include "PrintStatement.h"

PrintStatement::PrintStatement(InstructionNode *itemToPrint, BarrelParser &parser, PrintAs printAs)
    : InstructionNode{parser},
      m_itemToPrint{itemToPrint},
      m_printAs{printAs}
{
}

QVariant PrintStatement::exec()
{
    auto toPrint = m_itemToPrint->exec();
    switch (m_printAs)
    {
    case PrintAs::CharacterCodepoint:
        m_parser->print(static_cast<char>(toPrint.toDouble()));
        break;
    case PrintAs::Number:
        m_parser->print(toPrint.toDouble());
    default:
        break;
    }

    return {};
}
