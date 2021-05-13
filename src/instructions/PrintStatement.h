#ifndef PRINTSTATEMENT_H
#define PRINTSTATEMENT_H

#include "InstructionNode.h"

class PrintStatement : public InstructionNode
{
    Q_OBJECT

public:
    enum PrintAs
    {
        CharacterCodepoint,
        Number,
    };

    PrintStatement(InstructionNode *itemToPrint, BarrelParser &parser,
                   PrintAs printAs = PrintAs::CharacterCodepoint);

    QVariant exec() override;

private:
    PrintAs m_printAs;
    InstructionNode *m_itemToPrint;
};

#endif // PRINTSTATEMENT_H
