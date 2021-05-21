#include "InstructionChain.h"

#include "JumpStatement.h"
#include "JumpTarget.h"
#include "PrintStatement.h"

InstructionChain::InstructionChain(BarrelParser &parser) : InstructionNode{parser} {}

InstructionChain::InstructionChain(const InstructionChain &other)
    : InstructionNode{*other.m_parser},
      m_instructionChain{other.m_instructionChain}
{
}

void InstructionChain::addNode(InstructionNode *node)
{
    m_instructionChain.push_back(node);

    if (auto obj = dynamic_cast<JumpStatement *>(node))
    {
        connect(obj, &JumpStatement::jump, this, &InstructionChain::jump);
    }
}

QVariant InstructionChain::exec(ExecRole role)
{
    QVariant retVal;

    for (m_execLocation = 0; m_execLocation < m_instructionChain.length() && !m_parser->isDone();
         ++m_execLocation)
        retVal = m_instructionChain[m_execLocation]->exec(role);

    return retVal;
}

bool InstructionChain::hasAsChild(InstructionNode *other)
{
    for (auto item : m_instructionChain)
        if (item == other || item->hasAsChild(other))
            return true;

    return false;
}

bool InstructionChain::jumpToNode(InstructionNode *node)
{
    for (int i = 0; i < m_instructionChain.length(); ++i)
    {
        if (m_instructionChain[i] == node)
        {
            m_execLocation = i;
            return true;
        }
        else if (auto chain = dynamic_cast<InstructionChain *>(m_instructionChain[i]))
        {
            if (chain->jumpToNode(node))
                return true;
        }
    }

    return false;
}

void InstructionChain::jump(int numSpaces)
{
    if (numSpaces > 0)
        jumpForwards(numSpaces);
    else if (numSpaces < 0)
        jumpBackwards(-numSpaces); // negate numSpaces so that it is actually positive for the loop
    else
        ; // no jump at all
}

void InstructionChain::jumpForwards(int numSpaces)
{
    for (int i = m_execLocation, numJumps = 0;
         i < m_instructionChain.length() && numJumps < numSpaces; ++i)
    {
        if (dynamic_cast<JumpTarget *>(m_instructionChain[i]))
        {
            m_execLocation = i;
            ++numJumps;
        }
    }
}

void InstructionChain::jumpBackwards(int numSpaces)
{
    for (int i = m_execLocation, numJumps = 0; i > 0 && numJumps < numSpaces; --i)
    {
        if (dynamic_cast<JumpTarget *>(m_instructionChain[i]))
        {
            m_execLocation = i;
            ++numJumps;
        }
    }
}

// TODO: finish this?
void InstructionChain::condenseNodes()
{
    for (int i = 0; i < m_instructionChain.length(); ++i)
    {
        if (dynamic_cast<PrintStatement *>(m_instructionChain[i]))
        {
            int loc = i;

            while (dynamic_cast<PrintStatement *>(m_instructionChain[i]))
            {
                ++i;
            }

            QString content;

            for (int j = loc; j < i; ++j)
            {
            }
        }
    }
}
