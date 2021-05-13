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
