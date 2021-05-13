#ifndef RAISEACCTOPOWER_H
#define RAISEACCTOPOWER_H

#include "InstructionNode.h"
#include <QMap>

class RaiseAccToPower : public InstructionNode
{
    Q_OBJECT

public:
    RaiseAccToPower(InstructionNode *powerToRaiseTo, BarrelParser &parser);

    QVariant exec() override;

private:
    InstructionNode *m_powerToRaiseTo;
};

#endif // RAISEACCTOPOWER_H
