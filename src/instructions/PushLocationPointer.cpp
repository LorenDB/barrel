#include "PushLocationPointer.h"

PushLocationPointer::PushLocationPointer(BarrelParser &parser) : InstructionNode{parser} {}

QVariant PushLocationPointer::exec(ExecRole role)
{
    m_parser->pushLocationPointer(this);
    return {};
}
