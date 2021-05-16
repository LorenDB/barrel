#include "InstructionNode.h"

#include <QVariant>

InstructionNode::InstructionNode(BarrelParser &parser) : m_parser{&parser} {}

// TODO: implement this where necessary. Also use it for jumping and implement a jumpToChild function for if the child is found
bool InstructionNode::hasAsChild(InstructionNode *other)
{
    return false;
}

QVariant InstructionNode::exec()
{
    // do nothing; this should be overridden by subclasses
    return QVariant{};
}
