#ifndef BARRELPARSER_H
#define BARRELPARSER_H

#include <QChar>
#include <QMap>
#include <QObject>
#include <QStack>
#include <array>

class BarrelParser : public QObject
{
    Q_OBJECT
public:
    explicit BarrelParser(QObject *parent = nullptr);

    void run();
    void run(const QString &code);

signals:
    void done();

private:
    void parseLine(const QString &input);

    //! This will properly handle special number representatives.
    QPair<long double, int> getNumberString(const QString &string, const int &startingIndex);

    //! Handle printing things nicely.
    template<class T> void print(const T &itemToPrint);

    QMap<QChar, long double> m_numericShortcuts;
    QStack<int> m_locationPointerStack;

    // data storage for the program
    QStack<long double> m_stack;
    std::array<long double, 32> m_registers;
    std::array<long double, 2> m_controlRegisters;
    long double m_acc = 0;
    bool m_comparisonRegister;

    bool m_hasOutputThisRound = false;
    bool m_done = false;
};

#endif // BARRELPARSER_H
