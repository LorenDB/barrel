#include "BitShift.h"

BitShift::BitShift(InstructionNode *places, Direction direction, BarrelParser &parser)
    : InstructionNode{parser},
      m_places{places},
      m_direction{direction}
{
}

QVariant BitShift::exec(ExecRole role)
{
    auto places = m_places->exec(NumericalValue).toInt();
    m_parser->setAccumulator(m_direction == Left ?
                                 static_cast<int>(m_parser->accumulator()) << places :
                                 static_cast<int>(m_parser->accumulator()) >> places);
    return {m_parser->accumulator()};
}

bool BitShift::hasAsChild(InstructionNode *other)
{
    if (m_places == other || m_places->hasAsChild(other))
        return true;

    return false;
}
