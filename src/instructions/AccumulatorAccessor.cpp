#include "AccumulatorAccessor.h"

AccumulatorAccessor::AccumulatorAccessor(BarrelParser &parser) : InstructionNode{parser} {}

QVariant AccumulatorAccessor::exec(ExecRole role)
{
    return {m_parser->accumulator()};
}
