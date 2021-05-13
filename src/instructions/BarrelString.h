#ifndef BARRELSTRING_H
#define BARRELSTRING_H

#include "InstructionNode.h"

class BarrelString : public InstructionNode
{
    Q_OBJECT

public:
    BarrelString(const QString &string, BarrelParser &parser);

    QVariant exec() override;

private:
    QString m_string;
};

#endif // BARRELSTRING_H
