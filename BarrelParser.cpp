#include "BarrelParser.h"

#include <QRandomGenerator64>
#include <QtMath>

#include <iostream>

BarrelParser::BarrelParser(QObject *parent)
    : QObject(parent)
{
    m_numericShortcuts[L'½'] = 1 / 2;
    m_numericShortcuts[L'↉'] = 0;
    m_numericShortcuts[L'⅓'] = 1 / 3;
    m_numericShortcuts[L'⅔'] = 2 / 3;
    m_numericShortcuts[L'¼'] = 1 / 4;
    m_numericShortcuts[L'¾'] = 3 / 4;
    m_numericShortcuts[L'⅕'] = 1 / 5;
    m_numericShortcuts[L'⅖'] = 2 / 5;
    m_numericShortcuts[L'⅗'] = 3 / 5;
    m_numericShortcuts[L'⅘'] = 4 / 5;
    m_numericShortcuts[L'⅙'] = 1 / 6;
    m_numericShortcuts[L'⅚'] = 5 / 6;
    m_numericShortcuts[L'⅐'] = 1 / 7;
    m_numericShortcuts[L'⅛'] = 1 / 8;
    m_numericShortcuts[L'⅜'] = 3 / 8;
    m_numericShortcuts[L'⅝'] = 5 / 8;
    m_numericShortcuts[L'⅞'] = 7 / 8;
    m_numericShortcuts[L'⅑'] = 1 / 9;
    m_numericShortcuts[L'⅒'] = 1 / 10;
    m_numericShortcuts[L'π'] = M_PI;
    m_numericShortcuts['e'] = M_E;
    m_numericShortcuts[L'✓'] = true;
    m_numericShortcuts[L'❌'] = false; // this is NOT an ASCII 'X'
}

void BarrelParser::run(const QString &code)
{
     parseLine(code);
     m_done = true; // for completeness' sake; I don't actually think this is necessary
     emit done();
}

void BarrelParser::run()
{
    while (!m_done)
    {
        std::cout << "> ";
        std::string str;
        std::getline(std::cin, str);
        parseLine(QString::fromStdString(str));

        if (m_done)
            return;

        if (m_hasOutputThisRound)
        {
            std::cout << "\n";
            m_hasOutputThisRound = false;
        }
    }
}

void BarrelParser::parseLine(const QString &input)
{
    // index jump targets
    QVector<int> jumpTargetLocations;
    if (input.contains(L'¤'))
    {
        for (int i = 0; i < input.length(); ++i)
            if (input[i] == L'¤')
                jumpTargetLocations.push_back(i);
    }

    // now parse the command
    for (int i = 0; i < input.length(); ++i)
    {
        // single line commands
        if (input[i] == '+')
            ++m_acc;
        else if (input[i] == '-')
            --m_acc;
        else if (input[i] == L'±')
            m_acc = -m_acc;
        else if (input[i] == '|')
            m_acc = QRandomGenerator64::global()->generate64();
        else if (input[i] == 'p')
            print(static_cast<char>(m_acc));
        else if (input[i] == 'n')
            print(QString::number(static_cast<double>(m_acc)).toStdString());
        else if (input[i] == L'¶')
            print("\n");
        else if (input[i] == '[')
            m_stack.push(m_acc);
        else if (input[i] == L'¤' || input[i] == L'…')
            continue;

        else if (input[i] == '}')
        {
            if (m_stack.size() > 0)
                m_stack.pop();
        }
        else if (input[i] == ']')
        {
            if (m_stack.size() > 0)
                m_acc = m_stack.pop();
            else
                m_acc = QRandomGenerator64::global()->generate64();
        }
        else if (input[i] == L'√')
        {
            if (m_acc >= 0)
                m_acc = std::sqrt(m_acc);
        }
        else if (input[i] == '\'') // string
            for (++i; input[i] != '\'' && i < input.length(); ++i)
                print(input[i].toLatin1());

        // these require numeric parsing (combine all numeric parsing)
        else if (input[i] == '#' || input[i] == L'←' || input[i] == L'→' || input[i] == '^' || input[i] == '{' || input[i] == '&')
        {
            auto numData = getNumberString(input, i + 1);
            auto number = numData.first;

            // parse the command
            if (input[i] == '#')
            {
                parseLine(QString{static_cast<int>(number), input[i + numData.second + 1]});
                i += numData.second + 1; // get past the number
            }
            else if (input[i] == L'←')
            {
                // jumps imply pushing a location pointer
                m_locationPointerStack.push(i);

                int numJumpsFound = 0;
                for (int j = jumpTargetLocations.length() - 1; j >= 0; --j)
                {
                    if (jumpTargetLocations[j] < i) // this is a jump in the right direction
                        ++numJumpsFound;
                    if (numJumpsFound == number || j == 0)
                    {
                        i = jumpTargetLocations[j];
                        break;
                    }
                }
            }
            else if (input[i] == L'→')
            {
                m_locationPointerStack.push(i + numData.second); // add the offset for the number length

                int numJumpsFound = 0;
                for (int j = 0; j < jumpTargetLocations.length(); ++j)
                {
                    if (jumpTargetLocations[j] > i) // this is a jump in the right direction
                        ++numJumpsFound;

                    // either we found what we're looking for, or it's the last function, so we'll jump here
                    if (numJumpsFound == number || j == jumpTargetLocations.length() - 1)
                    {
                        i = jumpTargetLocations[j];
                        break;
                    }
                }
            }
            else if (input[i] == '^')
            {
                m_acc = number;
                i += numData.second;
            }
            else if (input[i] == '{')
            {
                m_stack.push(number);
                i += numData.second;
            }
            else if (input[i] == '&')
            {
                auto value = getNumberString(input, i + numData.second + 2); // assumes proper grammar -- maybe add validator?
                m_registers[static_cast<int>(number)] = value.first;
                i += numData.second + value.second + 1;
            }
        }

        // navigating locations
        else if (input[i] == L'↑')
        {
            if (!m_locationPointerStack.isEmpty())
                i = m_locationPointerStack.pop();
            else
            {
                m_done = true;
                emit done();
            }
        }
        else if (input[i] == L'↓')
            m_locationPointerStack.push(i);

        // if/else statement
        else if (input[i] == '?')
        {
//            bool hasEntireIfElse = false;
            QString ifElseString;
            for (int numColons = 0; numColons < 3; ++i)
            {
                if (input[i] == ':')
                    ++numColons;
                ifElseString.append(input[i]);
            }

            // delete the ?
            ifElseString.remove(0, 1);
            QStringList ops = ifElseString.split(':');
            parseLine(getNumberString(ops[0], 0).first ? ops[1] : ops[2]);

            // this is because i is currently past the end of the if statement, so this will offset the next increment
            --i;
        }

        // exit
        else if (input[i] == '!')
        {
            m_done = true;
            emit done();
        }

        else // implicitly print unknown characters
            print(input[i].toLatin1());
    }
}

QPair<long double, int> BarrelParser::getNumberString(const QString &string, const int &startingIndex)
{
    if (string[startingIndex] == 'a')
        return {m_acc, 1};
    else if (string[startingIndex] == '@')
    {
        auto number = getNumberString(string, startingIndex + 1);
        return {m_registers[static_cast<int>(number.first)], number.second + 1}; // + 1 for the @
    }
    else if (m_numericShortcuts.keys().contains(string[startingIndex]))
        return {m_numericShortcuts.value(string[startingIndex]), 1};

    QString numString;

    // get the whole number in string format
    for (int i = startingIndex; i < string.length() && string[i].isDigit(); ++i)
        numString.append(string[i]);

    // verify that this can be numberified
    bool gotDouble = false;
    numString.toDouble(&gotDouble);
    if (!gotDouble)
        qFatal("Not a number: %s", numString.toStdString().c_str());

    return {numString.toDouble(), numString.length()};
}

long double BarrelParser::getNumberFromString(const QString &string, const int &startingIndex)
{
    QString numString;

    // get the whole number in string format
    for (int i = startingIndex; i < string.length() && (string[i].isDigit() || string[i] == '.'); ++i)
        numString.append(string[i]);

    // parse to double
    long double number;
    bool gotDouble = false;
    number = numString.toDouble(&gotDouble);
    if (!gotDouble)
        qFatal("Not a number: %s", numString.toStdString().c_str());

    return number;
}

template<class T>
void BarrelParser::print(const T &itemToPrint)
{
    std::cout << itemToPrint;
    m_hasOutputThisRound = true;
}
