#include "IncrementAccumulator.h"

IncrementAccumulator::IncrementAccumulator(BarrelParser &parser) : InstructionNode{parser} {}

QVariant IncrementAccumulator::exec(ExecRole role)
{
    m_parser->setAccumulator(m_parser->accumulator() + 1);
    return {};
}
