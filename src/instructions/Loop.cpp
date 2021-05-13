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
    // make sure we only bother calculating the times once per execution
    auto times = m_times->exec().toInt();

    for (int i = 0; i < times; ++i)
        m_body->exec();

    return {};
}
