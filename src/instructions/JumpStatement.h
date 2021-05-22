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

    JumpStatement(InstructionNode *spaces, Direction direction, bool push, BarrelParser &parser);
    ~JumpStatement();

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

signals:
    void jump(int spaces);

private:
    InstructionNode *m_spacesToJump;
    Direction m_direction;
    bool m_push;
};

#endif // JUMPSTATEMENT_H
