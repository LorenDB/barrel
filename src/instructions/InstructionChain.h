#ifndef INSTRUCTIONCHAIN_H
#define INSTRUCTIONCHAIN_H

#include "InstructionNode.h"
#include <QObject>
#include <QVector>

class InstructionChain : public InstructionNode
{
    Q_OBJECT

public:
    explicit InstructionChain(BarrelParser &parser);
    InstructionChain(const InstructionChain &other);

    void addNode(InstructionNode *node);

    //! Executes the instruction chain and returns the
    //! return value from Barrel.
    QVariant exec() override;

    bool jumpToNode(InstructionNode *node);
    void condenseNodes();

signals:

public slots:
    void jump(int numSpaces);

private slots:
    void jumpForwards(int numSpaces);
    void jumpBackwards(int numSpaces);

private:
    QVector<InstructionNode *> m_instructionChain;
    int m_execLocation = 0;
};

#endif // INSTRUCTIONCHAIN_H
