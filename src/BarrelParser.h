#ifndef BARRELPARSER_H
#define BARRELPARSER_H

#include <QChar>
#include <QMap>
#include <QObject>
#include <QStack>
#include <array>

class InstructionChain;
class InstructionNode;

class BarrelParser : public QObject
{
    Q_OBJECT

public:
    explicit BarrelParser(QObject *parent = nullptr);

    void run();
    void run(const QString &code);

    //! Handle printing things nicely.
    template<typename T> void print(const T &itemToPrint);

    // these exist because my linker acts weird when calling the above function with some of the
    // fundamental types
    void print(const double &itemToPrint);
    void print(const char &itemToPrint);

    // convenience function
    void print(const QString &itemToPrint);

    bool isDone() const;
    double accumulator() const;
    void setAccumulator(double d);
    double topOfStack() const;
    void pushToStack(double d);
    double popFromStack();
    void setDone();
    double registerAt(int i) const;
    void setRegisterAt(int i, double value);
    double controlRegisterAt(int i) const;
    void setControlRegisterAt(int i, double value);
    void pushLocationPointer(InstructionNode *pointer);
    InstructionNode *popLocationPointer();

    InstructionChain *const instructionChain();

    constexpr static int ECHO_UNKNOWNS_REG = 0;
    constexpr static int FUZZY_COMPARE_REG = 1;

signals:
    void done();

private:
    InstructionChain *parseToInstructionChain(const QString &input);
    InstructionNode *getInstructionNode(QString &input);

    //! This will properly handle special number representatives.
    QPair<InstructionNode *, int> getNumberNode(QString &string);

    InstructionChain *m_instructionChain = nullptr;

    QMap<QChar, double> m_numericShortcuts;
    QMap<QChar, double> m_exponentShortcuts;
    QStack<InstructionNode *> m_locationPointerStack;

    // data storage for the program
    QStack<double> m_stack;
    std::array<double, 32> m_registers;
    std::array<double, 2> m_controlRegisters;
    double m_acc = 0;

    bool m_hasOutputThisRound = false;
    bool m_done = false;
};

#endif // BARRELPARSER_H
