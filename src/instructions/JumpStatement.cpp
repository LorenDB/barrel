#include "JumpStatement.h"

JumpStatement::JumpStatement(InstructionNode *spaces, Direction direction, bool push, BarrelParser &parser)
    : InstructionNode{parser},
      m_spacesToJump{spaces},
      m_direction{direction},
      m_push{push}
{
}

JumpStatement::~JumpStatement()
{
    delete m_spacesToJump;
}

QVariant JumpStatement::exec(ExecRole role)
{
    if (m_push)
        m_parser->pushLocationPointer(this);

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
