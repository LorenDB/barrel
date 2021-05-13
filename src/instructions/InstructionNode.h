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
    // TODO: set up destructor to delete any children nodes (pure virtual here; override elsewhere)

    //! This runs the instruction node. If the node evaluates to a value
    //! (as in accessors for the accumulator or stack), returns that value
    //! as a QVariant. If the node does not evaluate to anything, returns
    //! an empty QVariant.
    virtual QVariant exec() = 0;

    //! Find whether this node has another node as a child.
    // this should be overridden for nodes that have child nodes
    bool hasAsChild(InstructionNode *other);

signals:

protected:
    BarrelParser *m_parser = nullptr;
};

#endif // INSTRUCTIONNODE_H
