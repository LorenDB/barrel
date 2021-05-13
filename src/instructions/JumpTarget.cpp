#include "JumpTarget.h"

JumpTarget::JumpTarget(BarrelParser &parser) : InstructionNode{parser} {}

QVariant JumpTarget::exec()
{
    // this does nothing currently
    return {};
}
