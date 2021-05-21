#include "NegateAccumulator.h"

NegateAccumulator::NegateAccumulator(BarrelParser &parser) : InstructionNode{parser} {}

QVariant NegateAccumulator::exec(ExecRole role)
{
    m_parser->setAccumulator(-m_parser->accumulator());
    return {};
}
