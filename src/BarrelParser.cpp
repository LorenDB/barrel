#include "BarrelParser.h"

#include "instructions/Instructions.h"
#include <QRandomGenerator64>
#include <QtMath>
#include <iostream>

BarrelParser::BarrelParser(QObject *parent) : QObject(parent)
{
    // initalize the numeric shortcuts
    m_numericShortcuts[L'½'] = 1. / 2.;
    m_numericShortcuts[L'↉'] = 0;
    m_numericShortcuts[L'⅓'] = 1. / 3.;
    m_numericShortcuts[L'⅔'] = 2. / 3.;
    m_numericShortcuts[L'¼'] = 1. / 4.;
    m_numericShortcuts[L'¾'] = 3. / 4.;
    m_numericShortcuts[L'⅕'] = 1. / 5.;
    m_numericShortcuts[L'⅖'] = 2. / 5.;
    m_numericShortcuts[L'⅗'] = 3. / 5.;
    m_numericShortcuts[L'⅘'] = 4. / 5.;
    m_numericShortcuts[L'⅙'] = 1. / 6.;
    m_numericShortcuts[L'⅚'] = 5. / 6.;
    m_numericShortcuts[L'⅐'] = 1. / 7.;
    m_numericShortcuts[L'⅛'] = 1. / 8.;
    m_numericShortcuts[L'⅜'] = 3. / 8.;
    m_numericShortcuts[L'⅝'] = 5. / 8.;
    m_numericShortcuts[L'⅞'] = 7. / 8.;
    m_numericShortcuts[L'⅑'] = 1. / 9.;
    m_numericShortcuts[L'⅒'] = 1. / 10.;
    m_numericShortcuts[L'π'] = M_PI;
    m_numericShortcuts['e'] = M_E;
    m_numericShortcuts[L'✓'] = true;
    m_numericShortcuts[L'❌'] = false; // this is NOT an ASCII 'X'

    // initialize the exponent shortcuts
    m_exponentShortcuts[L'²'] = 2;
    m_exponentShortcuts[L'³'] = 3;
    m_exponentShortcuts[L'⁴'] = 4;
    m_exponentShortcuts[L'⁵'] = 5;
    m_exponentShortcuts[L'⁶'] = 6;
    m_exponentShortcuts[L'⁷'] = 7;
    m_exponentShortcuts[L'⁸'] = 8;
    m_exponentShortcuts[L'⁹'] = 9;
    m_exponentShortcuts[L'√'] = 1. / 2.;
    m_exponentShortcuts[L'∛'] = 1. / 3.;
    m_exponentShortcuts[L'∜'] = 1. / 4.;
    m_exponentShortcuts[L'₅'] = 1. / 5.;
    m_exponentShortcuts[L'₆'] = 1. / 6.;
    m_exponentShortcuts[L'₇'] = 1. / 7.;
    m_exponentShortcuts[L'₈'] = 1. / 8.;
    m_exponentShortcuts[L'₉'] = 1. / 9.;

    // initialize the control registers
    m_controlRegisters[ECHO_UNKNOWNS_REG] = true; // output unknown characters
    m_controlRegisters[FUZZY_COMPARE_REG] = 3; // fuzziness of fuzzy comparison
}

void BarrelParser::run(const QString &code)
{
    auto ic = parseToInstructionChain(code);
    ic->exec();
    setDone();
}

void BarrelParser::run()
{
    while (!m_done)
    {
        std::cout << "> ";
        std::string str;
        std::getline(std::cin, str);
        if (m_instructionChain)
            delete m_instructionChain;
        m_instructionChain = parseToInstructionChain(QString::fromStdString(str));
        m_instructionChain->exec();

        if (m_done)
            return;

        if (m_hasOutputThisRound)
        {
            std::cout << "\n";
            m_hasOutputThisRound = false;
        }
    }
}

InstructionChain *BarrelParser::parseToInstructionChain(const QString &input)
{
    InstructionChain *chain = new InstructionChain{*this};

    if (input.isEmpty() || input == "")
        chain->addNode(new ContinueStatement{*this});

    else
    {
        QString string{input};
        while (!string.isEmpty())
        {
            chain->addNode(getInstructionNode(string));
        }
    }

    return chain;
}

InstructionNode *BarrelParser::getInstructionNode(QString &input)
{
    // single character commands
    if (input[0] == '+')
    {
        input.remove(0, 1);
        return new IncrementAccumulator{*this};
    }
    else if (input[0] == '-')
    {
        input.remove(0, 1);
        return new DecrementAccumulator{*this};
    }
    else if (input[0] == L'±')
    {
        input.remove(0, 1);
        return new NegateAccumulator{*this};
    }
    else if (input[0] == '|')
    {
        input.remove(0, 1);
        return new RandomNumberGenerator{*this};
    }
    else if (input[0] == 'p')
    {
        input.remove(0, 1);
        return new PrintStatement{new AccumulatorAccessor{*this}, *this,
                                  PrintStatement::CharacterCodepoint};
    }
    else if (input[0] == 'n')
    {
        input.remove(0, 1);
        return new PrintStatement{new AccumulatorAccessor{*this}, *this, PrintStatement::Number};
    }
    else if (input[0] == L'¶')
    {
        input.remove(0, 1);
        return new PrintStatement{new BarrelString{"\n", *this}, *this};
    }
    else if (input[0] == '[')
    {
        input.remove(0, 1);
        return new PushToStack{new AccumulatorAccessor{*this}, *this};
    }
    else if (input[0] == L'√')
    {
        input.remove(0, 1);
        return new RaiseAccToPower{new Number{1. / 2., *this}, *this};
    }
    else if (input[0] == L'⅟')
    {
        input.remove(0, 1);
        return new ReciprocateAccumulator{*this};
    }
    else if (input[0] == L'∞')
    {
        input.remove(0, 1);
        return new Infinity{*this};
    }
    else if (input[0] == L'¤')
    {
        input.remove(0, 1);
        return new JumpTarget{*this};
    }
    else if (input[0] == L'…')
    {
        input.remove(0, 1);
        return new ContinueStatement{*this};
    }
    else if (input[0] == '}')
    {
        input.remove(0, 1);
        return new PopFromStack{*this};
    }
    else if (input[0] == ']')
    {
        input.remove(0, 1);
        return new SetAccumulator{new PopFromStack{*this}, *this};
    }
    else if (m_exponentShortcuts.contains(input[0]))
    {
        auto shortcut = input.at(0);
        input.remove(0, 1);
        return new RaiseAccToPower{new Number{m_exponentShortcuts[shortcut], *this}, *this};
    }

    else if (input[0] == '\'') // string
    {
        QString string;
        input.remove(0, 1);

        for (int i = 0; input[i] != '\'' && i < input.length(); ++i)
            string.append(input[i]);

        input.remove(0, string.length());

        if (string.length() > 0) // this means that there is a terminating ' left
            input.remove(0, 1);

        return new BarrelString{string, *this};
    }
    // these require numeric parsing (combine all numeric parsing)
    else if (input[0] == '#' || input[0] == L'←' || input[0] == L'→' || input[0] == L'↰' ||
             input[0] == L'↱' || input[0] == '^' || input[0] == '{' || input[0] == '&' ||
             input[0] == L'×' || input[0] == L'÷' || input[0] == L'«' || input[0] == L'»')
    {
        auto command = input.at(0); // save the command so we don't lose it due to the input string
                                    // chomping
        input.remove(0, 1);
        auto numData = getNumberNode(input);

        // parse the command
        if (command == '#')
        {
            auto body = getInstructionNode(input);
            return new Loop{numData.first, body, *this};
        }
        else if (command == L'←' || command == L'↰')
        {
            if (command == L'←')
            {
                auto chain = new InstructionChain{*this};
                chain->addNode(new PushLocationPointer{*this});
                chain->addNode(new JumpStatement{numData.first, JumpStatement::Backwards, *this});
                return chain;
            }
            else
                return new JumpStatement{numData.first, JumpStatement::Backwards, *this};
        }
        else if (command == L'→' || command == L'↱')
        {
            if (command == L'→')
            {
                auto chain = new InstructionChain{*this};
                chain->addNode(new PushLocationPointer{*this});
                chain->addNode(new JumpStatement{numData.first, JumpStatement::Forwards, *this});
                return chain;
            }
            else
                return new JumpStatement{numData.first, JumpStatement::Forwards, *this};
        }
        else if (command == '^')
            return new SetAccumulator{numData.first, *this};
        else if (command == '{')
            return new PushToStack{numData.first, *this};
        else if (command == '&')
        {
            if (input[0] != ':')
                ; // TODO: CRASH AND BURN

            input.remove(0, 1);
            auto val = getNumberNode(input);
            return new SetRegister{numData.first, val.first, *this};
        }
        else if (command == L'×')
            return new MultiplyStatement{numData.first, *this};
        else if (command == L'÷')
            return new DivideStatement{numData.first, *this};
        else if (command == L'«')
            return new BitShift{numData.first, BitShift::Left, *this};
        else if (command == L'»')
            return new BitShift{numData.first, BitShift::Right, *this};
        else // TODO: handle this more gracefully
            qFatal("Error: somehow the character \'%c\' got parsed where it shouldn't have.",
                   input[0].toLatin1());
    }

    else if (input[0] == 'a')
    {
        input.remove(0, 1);
        return new AccumulatorAccessor{*this};
    }
    else if (input[0] == '@')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new RegisterAccessor{number.first, *this};
    }
    else if (input[0] == L'¯')
    {
        input.remove(0, 1);
        return new StackAccessor{*this};
    }
    else if (input[0] == L'′')
    {
        input.remove(0, 1);
        return new PrimalityTest{new AccumulatorAccessor{*this}, *this};
    }
    else if (input[0] == '=')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new EqualTo{number.first, *this};
    }
    else if (input[0] == L'≈')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new FuzzyEqualTo{number.first, *this};
    }
    else if (input[0] == L'≠')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new NotEqualTo{number.first, *this};
    }
    else if (input[0] == L'≉')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new FuzzyNotEqualTo{number.first, *this};
    }
    else if (input[0] == '>')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new GreaterThan{number.first, *this};
    }
    else if (input[0] == '<')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new LessThan{number.first, *this};
    }
    else if (input[0] == L'≥')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new GreaterThanEqualTo{number.first, *this};
    }
    else if (input[0] == L'≤')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return new LessThanEqualTo{number.first, *this};
    }
    else if (m_numericShortcuts.keys().contains(input.at(0)))
    {
        auto num = input.at(0);
        input.remove(0, 1);
        return new Number{m_numericShortcuts.value(num), *this};
    }
    else if (input[0] == '(')
    {
        input.remove(0, 1);
        auto chain = new InstructionChain{*this};
        while (input[0] != ')')
            chain->addNode(getInstructionNode(input));
        return chain;
    }
    else if (input[0].isDigit())
    {
        QString numString;

        // get the whole number in string format
        for (int i = 0; i < input.length() && (input[i].isDigit() || input[i] == '.'); ++i)
            numString.append(input[i]);

        // verify that this can be numberified
        bool gotDouble = false;
        numString.toDouble(&gotDouble);
        if (!gotDouble)
        {
            input.remove(0, 1);
            return new Number{static_cast<double>(input[0].toLatin1()), *this}; // return the
                                                                                // char's
                                                                                // codepoint
        }

        input.remove(0, numString.length());
        return new Number{numString.toDouble(), *this};
    }

    // navigating locations
    else if (input[0] == L'↑')
    {
        input.remove(0, 1);
        return new PopLocationPointer{*this};
    }
    else if (input[0] == L'↓')
    {
        input.remove(0, 1);
        return new PushLocationPointer{*this};
    }

    // if/else statement
    else if (input[0] == '?')
    {
        // delete the ?
        input.remove(0, 1);

        QString ifElseString;
        for (int numColons = 0, i = 0; numColons < 3; ++i)
        {
            if (input[i] == ':')
                ++numColons;
            ifElseString.append(input[i]);
        }

        input.remove(0, ifElseString.length());

        QStringList ops = ifElseString.split(':');

        return new IfElse{parseToInstructionChain(ops[0]), parseToInstructionChain(ops[1]),
                          parseToInstructionChain(ops[2]), *this};
    }

    // exit
    else if (input[0] == '!')
    {
        input.remove(0, 1);
        return new ExitStatement{*this};
    }

    else // implicitly print unknown characters
    {
        input.remove(0, 1);
        return new PrintStatement{new BarrelString{QChar{input[0]}, *this}, *this};
    }
}

// TODO: this contains a lot of stuff that is duplicated; it'd be nice to move everything here back
// into getInstructionNode (this should be feasable, although it could make for some fascinating
// runtime and/or logic errors)
QPair<InstructionNode *, int> BarrelParser::getNumberNode(QString &input)
{
    if (input[0] == 'a')
    {
        input.remove(0, 1);
        return {new AccumulatorAccessor{*this}, 1};
    }
    else if (input[0] == L'∞')
    {
        input.remove(0, 1);
        return {new Infinity{*this}, 1};
    }
    else if (input[0] == '@')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new RegisterAccessor{number.first, *this}, number.second};
    }
    else if (input[0] == L'¯')
    {
        input.remove(0, 1);
        return {new StackAccessor{*this}, 1};
    }
    else if (input[0] == L'′')
    {
        input.remove(0, 1);
        return {new PrimalityTest{new AccumulatorAccessor{*this}, *this}, 1};
    }
    else if (input[0] == '=')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new EqualTo{number.first, *this}, number.second};
    }
    else if (input[0] == L'≈')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new FuzzyEqualTo{number.first, *this}, number.second};
    }
    else if (input[0] == L'≠')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new NotEqualTo{number.first, *this}, number.second};
    }
    else if (input[0] == L'≉')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new FuzzyNotEqualTo{number.first, *this}, number.second};
    }
    else if (input[0] == '>')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new GreaterThan{number.first, *this}, number.second};
    }
    else if (input[0] == '<')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new LessThan{number.first, *this}, number.second};
    }
    else if (input[0] == L'≥')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new GreaterThanEqualTo{number.first, *this}, number.second};
    }
    else if (input[0] == L'≤')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        input.remove(0, number.second);
        return {new LessThanEqualTo{number.first, *this}, number.second};
    }
    else if (m_numericShortcuts.keys().contains(input.at(0)))
    {
        auto num = input.at(0);
        input.remove(0, 1);
        return {new Number{m_numericShortcuts.value(num), *this}, 1};
    }

    QString numString;

    // get the whole number in string format
    for (int i = 0; i < input.length() && (input[i].isDigit() || input[i] == '.'); ++i)
        numString.append(input[i]);

    // verify that this can be numberified
    bool gotDouble = false;
    numString.toDouble(&gotDouble);
    if (!gotDouble)
    {
        input.remove(0, 1);
        return {new Number{static_cast<double>(input[0].toLatin1()), *this}, 1}; // return the
                                                                                 // char's
                                                                                 // codepoint
    }

    input.remove(0, numString.length());
    return {new Number{numString.toDouble(), *this}, numString.length()};
}

template<typename T> void BarrelParser::print(const T &itemToPrint)
{
    std::cout << itemToPrint;
    std::cout.flush(); // make sure to print
    m_hasOutputThisRound = true;
}

void BarrelParser::print(const double &itemToPrint)
{
    std::cout << itemToPrint;
    std::cout.flush(); // make sure to print
    m_hasOutputThisRound = true;
}

void BarrelParser::print(const char &itemToPrint)
{
    std::cout << itemToPrint;
    std::cout.flush(); // make sure to print
    m_hasOutputThisRound = true;
}

void BarrelParser::print(const QString &itemToPrint)
{
    std::cout << itemToPrint.toStdString();
    std::cout.flush(); // make sure to print
    m_hasOutputThisRound = true;
}

bool BarrelParser::isDone() const
{
    return m_done;
}

double BarrelParser::accumulator() const
{
    return m_acc;
}

void BarrelParser::setAccumulator(double d)
{
    m_acc = d;
}

double BarrelParser::topOfStack() const
{
    return m_stack.top();
}

void BarrelParser::pushToStack(double d)
{
    m_stack.push(d);
}

double BarrelParser::popFromStack()
{
    return m_stack.size() > 0 ? m_stack.pop() : QRandomGenerator64::global()->generate64();
}

void BarrelParser::setDone()
{
    m_done = true;
    emit done();
}

double BarrelParser::registerAt(int i) const
{
    return m_registers[i];
}

void BarrelParser::setRegisterAt(int i, double value)
{
    m_registers[i] = value;
}

double BarrelParser::controlRegisterAt(int i) const
{
    return m_controlRegisters[i];
}

void BarrelParser::setControlRegisterAt(int i, double value)
{
    m_controlRegisters[i] = value;
}

void BarrelParser::pushLocationPointer(InstructionNode *pointer)
{
    m_locationPointerStack.push_back(pointer);
}

InstructionNode *BarrelParser::popLocationPointer()
{
    if (!m_locationPointerStack.isEmpty())
        return m_locationPointerStack.pop();
    else
    {
        m_done = true;
        emit done();
        return nullptr;
    }
}

InstructionChain *const BarrelParser::instructionChain()
{
    return m_instructionChain;
}
