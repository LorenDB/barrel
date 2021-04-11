#ifndef BARRELPARSER_H
#define BARRELPARSER_H

#include <QObject>
#include <QStack>
#include <QMap>
#include <QChar>

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
    void done_p();

private:
    void parseLine(QString input);
    int getIntFromString(const QString &string, const int &startingIndex);

    /*const*/ QMap<QChar, double> m_numericShortcuts;

    QStack<double> m_stack;
    std::array<int, 32> m_registers;
    double m_acc = 0;

    bool m_done = false;
};

#endif // BARRELPARSER_H
