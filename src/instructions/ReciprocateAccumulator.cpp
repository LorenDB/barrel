#include "ReciprocateAccumulator.h"

ReciprocateAccumulator::ReciprocateAccumulator(BarrelParser &parser) : InstructionNode{parser} {}

QVariant ReciprocateAccumulator::exec(ExecRole role)
{
    m_parser->setAccumulator(1 / m_parser->accumulator());
    return {m_parser->accumulator()};
}
