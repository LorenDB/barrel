#include "ExitStatement.h"

ExitStatement::ExitStatement(BarrelParser &parser) : InstructionNode{parser} {}

QVariant ExitStatement::exec(ExecRole role)
{
    m_parser->setDone();

    return {0};
}
