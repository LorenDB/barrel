#include "ExitStatement.h"

ExitStatement::ExitStatement(BarrelParser &parser) : InstructionNode{parser} {}

QVariant ExitStatement::exec()
{
    m_parser->setDone();
    return {};
}
