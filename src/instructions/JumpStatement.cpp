#include "JumpStatement.h"

JumpStatement::JumpStatement(InstructionNode *spaces, Direction direction, BarrelParser &parser)
    : InstructionNode{parser},
      m_spacesToJump{spaces},
      m_direction{direction}
{
}

QVariant JumpStatement::exec(ExecRole role)
{
    auto spaces = m_spacesToJump->exec(NumericalValue).toInt();

    // if jumping backwards, make sure to use a negative direction
    emit jump(m_direction == Forwards ? spaces : -spaces);

    // this seems wacky, but we need to cover every case
    if (role == NumericalValue)
        return {spaces};

    return QVariant{};
}

bool JumpStatement::hasAsChild(InstructionNode *other)
{
    if (m_spacesToJump == other || m_spacesToJump->hasAsChild(other))
        return true;

    return false;
}
