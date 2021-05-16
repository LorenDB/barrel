#include "RaiseAccToPower.h"

#include <cmath>

RaiseAccToPower::RaiseAccToPower(InstructionNode *powerToRaiseTo, BarrelParser &parser)
    : InstructionNode{parser},
      m_powerToRaiseTo{powerToRaiseTo}
{
}

QVariant RaiseAccToPower::exec()
{
    auto a = m_parser->accumulator();
    auto b = m_powerToRaiseTo->exec();
    auto c = b.toDouble();
    auto d = std::pow(a, c);
    m_parser->setAccumulator(d);
    //    m_parser->setAccumulator(std::pow(m_parser->accumulator(),
    //    m_powerToRaiseTo->exec().toDouble()));
    return {m_parser->accumulator()};
}

bool RaiseAccToPower::hasAsChild(InstructionNode *other)
{
    if (m_powerToRaiseTo == other || m_powerToRaiseTo->hasAsChild(other))
        return true;

    return false;
}
