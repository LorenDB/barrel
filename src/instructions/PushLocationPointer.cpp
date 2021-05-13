#include "PushLocationPointer.h"

PushLocationPointer::PushLocationPointer(BarrelParser &parser) : InstructionNode{parser} {}

QVariant PushLocationPointer::exec()
{
    m_parser->pushLocationPointer(this);
    return {};
}
