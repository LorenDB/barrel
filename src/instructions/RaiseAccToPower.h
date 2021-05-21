#ifndef RAISEACCTOPOWER_H
#define RAISEACCTOPOWER_H

#include "InstructionNode.h"
#include <QMap>

class RaiseAccToPower : public InstructionNode
{
    Q_OBJECT

public:
    RaiseAccToPower(InstructionNode *powerToRaiseTo, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;

private:
    InstructionNode *m_powerToRaiseTo;
};

#endif // RAISEACCTOPOWER_H
