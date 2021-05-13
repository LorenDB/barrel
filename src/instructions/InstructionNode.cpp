#include "InstructionNode.h"

#include <qvariant.h>

InstructionNode::InstructionNode(BarrelParser &parser) : m_parser{&parser} {}

bool InstructionNode::hasAsChild(InstructionNode *other)
{
    return false;
}

QVariant InstructionNode::exec()
{
    // do nothing; this should be overridden by subclasses
    return QVariant{};
}
