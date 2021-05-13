#include "PopFromStack.h"

PopFromStack::PopFromStack(BarrelParser &parser) : InstructionNode{parser} {}

QVariant PopFromStack::exec()
{
    return {m_parser->popFromStack()};
}
