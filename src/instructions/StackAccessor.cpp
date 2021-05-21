#include "StackAccessor.h"

StackAccessor::StackAccessor(BarrelParser &parser) : InstructionNode{parser} {}

QVariant StackAccessor::exec(ExecRole role)
{
    return m_parser->topOfStack();
}
