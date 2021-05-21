#ifndef INSTRUCTIONNODE_H
#define INSTRUCTIONNODE_H

#include "../BarrelParser.h"
#include <QObject>
#include <QVariant>
#include <QVector>

class InstructionNode : public QObject
{
    Q_OBJECT

public:
    explicit InstructionNode(BarrelParser &parser);

    // If you are subclassing InstructionNode, make sure that you implement a destructor if you have
    // any child pointers to other InstructionNodes. If you want an example, see
    // InstructionChain.cpp.

    enum ExecRole
    {
        Default,
        NumericalValue,
    };

    //! This runs the instruction node. If the node evaluates to a value
    //! (as in accessors for the accumulator or stack), returns that value
    //! as a QVariant. If the node does not evaluate to anything, returns
    //! an empty QVariant.
    virtual QVariant exec(ExecRole role = Default) = 0;

    //! Find whether this node has another node as a child.
    // this should be overridden for nodes that have child nodes
    virtual bool hasAsChild(InstructionNode *other);

signals:

protected:
    BarrelParser *m_parser = nullptr;
};

#endif // INSTRUCTIONNODE_H
