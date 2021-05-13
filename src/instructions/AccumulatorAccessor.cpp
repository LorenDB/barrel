#include "AccumulatorAccessor.h"

AccumulatorAccessor::AccumulatorAccessor(BarrelParser &parser) : InstructionNode{parser} {}

QVariant AccumulatorAccessor::exec()
{
    return {m_parser->accumulator()};
}
