#ifndef JUMPSTATEMENT_H
#define JUMPSTATEMENT_H

#include "InstructionNode.h"
#include <QObject>

class JumpStatement : public InstructionNode
{
    Q_OBJECT

public:
    enum Direction
    {
        Backwards,
        Forwards,
    };

    JumpStatement(InstructionNode *spaces, Direction direction, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

signals:
    void jump(int spaces);

private:
    InstructionNode *m_spacesToJump;
    Direction m_direction;
};

#endif // JUMPSTATEMENT_H
