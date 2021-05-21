#include "ContinueStatement.h"

ContinueStatement::ContinueStatement(BarrelParser &parser) : InstructionNode{parser} {}

QVariant ContinueStatement::exec(ExecRole role)
{
    // this is a "do-nothing" statement
    return {};
}
