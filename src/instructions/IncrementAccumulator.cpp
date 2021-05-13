#include "IncrementAccumulator.h"

IncrementAccumulator::IncrementAccumulator(BarrelParser &parser) : InstructionNode{parser} {}

QVariant IncrementAccumulator::exec()
{
    m_parser->setAccumulator(m_parser->accumulator() + 1);
    return {};
}
