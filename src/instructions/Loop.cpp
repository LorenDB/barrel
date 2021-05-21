#include "Loop.h"

#include "Infinity.h"

Loop::Loop(InstructionNode *times, InstructionNode *body, BarrelParser &parser)
    : InstructionNode{parser},
      m_times{times},
      m_body{body}
{
}

QVariant Loop::exec(ExecRole role)
{
    QVariant ret;

    if (dynamic_cast<Infinity *>(m_times))
    {
        while (true)
            m_body->exec(role);
    }
    else
    {
        // make sure we only bother calculating the times once per execution
        auto times = m_times->exec().toInt();

        for (int i = 0; i < times; ++i)
            ret = m_body->exec();
    }

    return ret;
}

bool Loop::hasAsChild(InstructionNode *other)
{
    if (m_times == other || m_body == other || m_times->hasAsChild(other) || m_body->hasAsChild(other))
        return true;

    return false;
}
