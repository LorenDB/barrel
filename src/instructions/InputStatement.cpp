#include "InputStatement.h"

#include <iostream>
#include <limits>

InputStatement::InputStatement(BarrelParser &parser) : InstructionNode{parser} {}

QVariant InputStatement::exec(ExecRole role)
{
    double d = m_parser->getInput();
    m_parser->setAccumulator(d);

    return {d};
}
