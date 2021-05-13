#include "DecrementAccumulator.h"

DecrementAccumulator::DecrementAccumulator(BarrelParser &parser) : InstructionNode{parser} {}

QVariant DecrementAccumulator::exec()
{
    m_parser->setAccumulator(m_parser->accumulator() - 1);
    return {};
}
