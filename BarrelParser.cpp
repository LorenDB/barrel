#include "BarrelParser.h"

#include <QRandomGenerator64>

#include <iostream>

BarrelParser::BarrelParser(QObject *parent)
    : QObject(parent)
{
    m_numericShortcuts[L'⅐'] = 1 / 7;
    m_numericShortcuts[L'⅑'] = 1 / 9;
    m_numericShortcuts[L'⅓'] = 1 / 2;
    m_numericShortcuts[L'⅔'] = 2 / 3;
    m_numericShortcuts[L'⅕'] = 1 / 5;
    m_numericShortcuts[L'⅖'] = 2 / 5;
    m_numericShortcuts[L'⅗'] = 3 / 5;
    m_numericShortcuts[L'⅘'] = 4 / 5;
    m_numericShortcuts[L'⅙'] = 1 / 6;
    m_numericShortcuts[L'⅚'] = 5 / 6;
    m_numericShortcuts[L'⅛'] = 1 / 8;
    m_numericShortcuts[L'⅜'] = 3 / 8;
    m_numericShortcuts[L'⅝'] = 5 / 8;
    m_numericShortcuts[L'⅞'] = 7 / 8;

    connect(this, &BarrelParser::done_p, this, [this] {
        m_done = true;
        emit done();
    });
}

void BarrelParser::run(const QString &code)
{
     parseLine(code);
    emit done_p();
}

void BarrelParser::run()
{
    while (!m_done)
    {
        std::cout << "> ";
        std::string str;
        std::getline(std::cin, str);
        parseLine(QString::fromStdString(str));
    }
}

void BarrelParser::parseLine(QString input)
{
    for (int i = 0; i < input.length(); ++i)
    {
        // single line commands
        if (input[i] == '+')
            ++m_acc;
        else if (input[i] == '-')
            --m_acc;
        else if (input[i] == 'p')
            std::cout << static_cast<char>(m_acc);
        else if (input[i] == 'n')
            std::cout << QString::number(m_acc).toStdString();
        else if (input[i] == '[')
            m_stack.push(m_acc);

        else if (input[i] == '!')
            emit done_p();
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
        else if (input[i] == '\'') // string
            for (++i; input[i] != '\'' && i < input.length(); ++i)
                std::cout << input[i].toLatin1();

        // this require numeric parsing (combine all numeric parsing)
        else if (input[i] == '#' || input[i] == '<' || input[i] == '>' || input[i] == '^' || input[i] == '{' || input[i] == '&')
        {
            double number;
            QString numString;

            if (input[i + 1] == 'a')
            {
                number = m_acc;
                numString.append('a'); // give it a length of one for later calculations
            }
            else if (input[i + 1] == '|')
            {
                number = QRandomGenerator64::global()->generate64();
                numString = '|';
            }
            else if (input[i + 1] == '@')
            {
                number = getIntFromString(input, i + 2);
                numString = QString::number(number).prepend('@');
                number = m_registers[number];
            }
            else if (m_numericShortcuts.keys().contains(input[i + 1]))
            {
                number = m_numericShortcuts.value(input[i + 1]); //  [input[i + 1]];
                numString.append(input[i + 1]);
            }
            else
            {
                number = getIntFromString(input, i + 1);
                numString = QString::number(number);
            }

            // parse the command
            if (input[i] == '#')
                input.replace(i + 1, numString.length() + 1, QString{static_cast<int>(number), input[i + numString.length() + 1]});
            else if (input[i] == '<')
                i -= (number);
            else if (input[i] == '>')
                i += (number + numString.length() + 1);
            else if (input[i] == '^')
            {
                m_acc = number;
                i += numString.length();
            }
            else if (input[i] == '{')
            {
                m_stack.push(number);
                i += numString.length();
            }
            else if (input[i] == '&')
            {
                auto value = getIntFromString(input, i + numString.length() + 2); // assumes proper grammar -- maybe add validator?
                m_registers[static_cast<int>(number)] = value;
                i += numString.length() + QString::number(value).length() + 1;
            }
        }

        // if/else statement
        else if (input[i] == '?')
        {
//            bool hasEntireIfElse = false;
            QString ifElseString;
            for (int numDollarSigns = 0; numDollarSigns < 3; ++i)
            {
                if (input[i] == '$')
                    ++numDollarSigns;
                ifElseString.append(input[i]);
            }

            // delete the ?
            ifElseString.remove(0, 1);

            QStringList ops = ifElseString.split('$');

            if (ops[0] == 'T')
                parseLine(ops[1]);
            else if (ops[0] == 'F')
                parseLine(ops[2]);
            else if (ops[0] == "a")
                parseLine(m_acc ? ops[1] : ops[2]);

            --i;
        }

        else // implicitly print unknown characters
            std::cout << input[i].toLatin1();

        std::cout << "\n";
    }
}

int BarrelParser::getIntFromString(const QString &string, const int &startingIndex)
{
    QString numString;

    // get the whole number in string format
    for (int i = startingIndex; i < string.length() && string[i].isDigit(); ++i)
        numString.append(string[i]);

    // parse to int
    int number;
    bool gotInt = false;
    number = numString.toInt(&gotInt);
    if (!gotInt)
        qFatal("Not a number: %s", numString.toStdString().c_str());

    return number;
}
