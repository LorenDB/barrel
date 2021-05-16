#include "IfElse.h"

IfElse::IfElse(InstructionNode *evalNode, InstructionNode *truthyNode, InstructionNode *falseyNode,
               BarrelParser &parser)
    : InstructionNode{parser},
      m_evalNode{evalNode},
      m_truthyNode{truthyNode},
      m_falseyNode{falseyNode}
{
}

QVariant IfElse::exec()
{
    auto value = m_evalNode->exec();
    if (value.isValid())
    {
        if (value.toBool() || value.toDouble() || value.toInt())
            return m_truthyNode->exec();
        else
            return m_falseyNode->exec();
    }
    else
        return {}; // RAISE EXCEPTION OR SOMETHING
}

bool IfElse::hasAsChild(InstructionNode *other)
{
    if (m_evalNode == other || m_truthyNode == other || m_falseyNode == other || m_evalNode->hasAsChild(other) || m_truthyNode->hasAsChild(other) || m_falseyNode->hasAsChild(other))
        return true;

    return false;
}
