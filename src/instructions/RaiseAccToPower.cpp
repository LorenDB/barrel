#include "RaiseAccToPower.h"

#include <cmath>

RaiseAccToPower::RaiseAccToPower(InstructionNode *powerToRaiseTo, BarrelParser &parser)
    : InstructionNode{parser},
      m_powerToRaiseTo{powerToRaiseTo}
{
}

RaiseAccToPower::~RaiseAccToPower()
{
    delete m_powerToRaiseTo;
}

QVariant RaiseAccToPower::exec(ExecRole role)
{
    m_parser->setAccumulator(
        std::pow(m_parser->accumulator(), m_powerToRaiseTo->exec(NumericalValue).toDouble()));
    return {m_parser->accumulator()};
}

bool RaiseAccToPower::hasAsChild(InstructionNode *other)
{
    if (m_powerToRaiseTo == other || m_powerToRaiseTo->hasAsChild(other))
        return true;

    return false;
}
