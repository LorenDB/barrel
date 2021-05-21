#include "PopFromStack.h"

PopFromStack::PopFromStack(BarrelParser &parser) : InstructionNode{parser} {}

QVariant PopFromStack::exec(ExecRole role)
{
    return {m_parser->popFromStack()};
}
