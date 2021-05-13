#include "ContinueStatement.h"

ContinueStatement::ContinueStatement(BarrelParser &parser) : InstructionNode{parser} {}

QVariant ContinueStatement::exec()
{
    // this is a "do-nothing" statement
    return {};
}
