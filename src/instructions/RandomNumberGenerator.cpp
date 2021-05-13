#include "RandomNumberGenerator.h"

#include "QRandomGenerator64"

RandomNumberGenerator::RandomNumberGenerator(BarrelParser &parser) : InstructionNode{parser} {}

QVariant RandomNumberGenerator::exec()
{
    m_parser->setAccumulator(QRandomGenerator64::global()->generate64());
    return {};
}
