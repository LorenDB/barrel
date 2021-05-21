#include "JumpTarget.h"

JumpTarget::JumpTarget(BarrelParser &parser) : InstructionNode{parser} {}

QVariant JumpTarget::exec(ExecRole role)
{
    // this does nothing
    return {};
}
