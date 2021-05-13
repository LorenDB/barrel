#include "PopLocationPointer.h"

#include "InstructionChain.h"

PopLocationPointer::PopLocationPointer(BarrelParser &parser) : InstructionNode{parser} {}

QVariant PopLocationPointer::exec()
{
    auto jumpTo = m_parser->popLocationPointer();
    if (jumpTo)
        m_parser->instructionChain()->jumpToNode(jumpTo);
    return {};
}
