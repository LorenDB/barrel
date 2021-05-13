#include "StackAccessor.h"

StackAccessor::StackAccessor(BarrelParser &parser) : InstructionNode{parser} {}

QVariant StackAccessor::exec()
{
    return m_parser->topOfStack();
}
