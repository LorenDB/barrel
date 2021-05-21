#include "IfElse.h"

IfElse::IfElse(InstructionNode *evalNode, InstructionNode *truthyNode, InstructionNode *falseyNode,
               BarrelParser &parser)
    : InstructionNode{parser},
      m_evalNode{evalNode},
      m_truthyNode{truthyNode},
      m_falseyNode{falseyNode}
{
}

IfElse::~IfElse()
{
    delete m_evalNode;
    delete m_truthyNode;
    delete m_falseyNode;
}

QVariant IfElse::exec(ExecRole role)
{
    auto value = m_evalNode->exec(NumericalValue);

    if (value.toBool() || value.toDouble() || value.toInt())
        return m_truthyNode->exec(role);
    else
        return m_falseyNode->exec(role);
}

bool IfElse::hasAsChild(InstructionNode *other)
{
    if (m_evalNode == other || m_truthyNode == other || m_falseyNode == other ||
        m_evalNode->hasAsChild(other) || m_truthyNode->hasAsChild(other) ||
        m_falseyNode->hasAsChild(other))
        return true;

    return false;
}
