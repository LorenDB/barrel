#include "SquareRootAcc.h"

#include <cmath>

SquareRootAcc::SquareRootAcc(BarrelParser &parser) : InstructionNode{parser} {}

QVariant SquareRootAcc::exec()
{
    if (m_parser->accumulator() >= 0)
        m_parser->setAccumulator(std::sqrt(m_parser->accumulator()));
    return {};
}