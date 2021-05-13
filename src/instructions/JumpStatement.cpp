#include "JumpStatement.h"

JumpStatement::JumpStatement(InstructionNode *spaces, Direction direction, BarrelParser &parser)
    : InstructionNode{parser},
      m_spacesToJump{spaces},
      m_direction{direction}
{
}

QVariant JumpStatement::exec()
{
    auto spaces = m_spacesToJump->exec().toInt();
    emit jump(m_direction == Forwards ? spaces : -spaces); // if jumping backwards, make sure to use
                                                           // a negative direction

    return QVariant{};
}
