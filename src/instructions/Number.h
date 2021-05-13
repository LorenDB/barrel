#ifndef NUMBER_H
#define NUMBER_H

#include "InstructionNode.h"

class Number : public InstructionNode
{
    Q_OBJECT

public:
    Number(double value, BarrelParser &parser);

    QVariant exec() override;

private:
    double m_value;
};

#endif // NUMBER_H
