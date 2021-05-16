#include "Loop.h"

#include "Infinity.h"

Loop::Loop(InstructionNode *times, InstructionNode *body, BarrelParser &parser)
    : InstructionNode{parser},
      m_times{times},
      m_body{body}
{
}

QVariant Loop::exec()
{
    if (dynamic_cast<Infinity *>(m_times))
    {
        while (true)
            m_body->exec();
    }
    else
    {
        // make sure we only bother calculating the times once per execution
        auto times = m_times->exec().toInt();

        for (int i = 0; i < times; ++i)
            m_body->exec();
    }

    return {};
}

bool Loop::hasAsChild(InstructionNode *other)
{
    if (m_times == other || m_body == other || m_times->hasAsChild(other) || m_body->hasAsChild(other))
        return true;

    return false;
}
