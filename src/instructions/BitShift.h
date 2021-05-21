#ifndef BITSHIFT_H
#define BITSHIFT_H

#include "InstructionNode.h"

class BitShift : public InstructionNode
{
    Q_OBJECT

public:
    enum Direction
    {
        Left,
        Right,
    };

    BitShift(InstructionNode *places, Direction direction, BarrelParser &parser);
    ~BitShift();

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_places;
    Direction m_direction;
};

#endif // BITSHIFT_H
