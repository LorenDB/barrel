#include "BitShift.h"

BitShift::BitShift(InstructionNode *places, Direction direction, BarrelParser &parser)
    : InstructionNode{parser},
      m_places{places},
      m_direction{direction}
{
}

QVariant BitShift::exec()
{
    auto places = m_places->exec().toInt();
    m_parser->setAccumulator(m_direction == Left ?
                                 static_cast<int>(m_parser->accumulator()) << places :
                                 static_cast<int>(m_parser->accumulator()) >> places);
    return {m_parser->accumulator()};
}
