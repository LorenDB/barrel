#ifndef NOTEQUALTO_H
#define NOTEQUALTO_H

#include "EqualityOperation.h"

class NotEqualTo : public EqualityOperation
{
    Q_OBJECT

public:
    NotEqualTo(InstructionNode *valueToCompareTo, BarrelParser &parser);

    QVariant exec(ExecRole role = Default) override;
    bool hasAsChild(InstructionNode *other) override;
};

#endif // NOTEQUALTO_H
