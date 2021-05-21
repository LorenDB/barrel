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
    // if no input, just continue
    if (input.isEmpty())
        return new ContinueStatement{*this};

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
        return new BarrelString{"\n", *this};
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
    else if (input[0] == 'a')
    {
        input.remove(0, 1);
        return new AccumulatorAccessor{*this};
    }
    else if (input[0] == '@')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new RegisterAccessor{number, *this};
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
        return new EqualTo{number, *this};
    }
    else if (input[0] == L'≈')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new FuzzyEqualTo{number, *this};
    }
    else if (input[0] == L'≠')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new NotEqualTo{number, *this};
    }
    else if (input[0] == L'≉')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new FuzzyNotEqualTo{number, *this};
    }
    else if (input[0] == '>')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new GreaterThan{number, *this};
    }
    else if (input[0] == '<')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new LessThan{number, *this};
    }
    else if (input[0] == L'≥')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new GreaterThanEqualTo{number, *this};
    }
    else if (input[0] == L'≤')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new LessThanEqualTo{number, *this};
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
        while (!input.isEmpty() && input[0] != ')')
            chain->addNode(getInstructionNode(input));

        // remove the ')'
        input.remove(0, 1);

        return chain;
    }
    else if (input[0] == L'λ')
    {
        input.remove(0, 1);
        return new InputStatement{*this};
    }

    // string
    else if (input[0] == '\'')
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
        auto number = getNumberNode(input);

        // parse the command
        if (command == '#')
        {
            auto body = getInstructionNode(input);
            return new Loop{number, body, *this};
        }
        else if (command == L'←' || command == L'↰')
        {
            if (command == L'←')
            {
                auto chain = new InstructionChain{*this};
                chain->addNode(new PushLocationPointer{*this});
                chain->addNode(new JumpStatement{number, JumpStatement::Backwards, *this});
                return chain;
            }
            else
                return new JumpStatement{number, JumpStatement::Backwards, *this};
        }
        else if (command == L'→' || command == L'↱')
        {
            if (command == L'→')
            {
                auto chain = new InstructionChain{*this};
                chain->addNode(new PushLocationPointer{*this});
                chain->addNode(new JumpStatement{number, JumpStatement::Forwards, *this});
                return chain;
            }
            else
                return new JumpStatement{number, JumpStatement::Forwards, *this};
        }
        else if (command == '^')
            return new SetAccumulator{number, *this};
        else if (command == '{')
            return new PushToStack{number, *this};
        else if (command == '&')
        {
            if (input[0] != ':')
                ; // TODO: CRASH AND BURN

            input.remove(0, 1);
            auto val = getNumberNode(input);
            return new SetRegister{number, val, *this};
        }
        else if (command == L'×')
            return new MultiplyStatement{number, *this};
        else if (command == L'÷')
            return new DivideStatement{number, *this};
        else if (command == L'«')
            return new BitShift{number, BitShift::Left, *this};
        else if (command == L'»')
            return new BitShift{number, BitShift::Right, *this};
        else // TODO: handle this more gracefully
            qFatal("Error: somehow the character \'%c\' got parsed where it shouldn't have.",
                   input[0].toLatin1());
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
            // return the char's codepoint
            return new Number{static_cast<double>(input[0].toLatin1()), *this};
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
        for (int numColons = 0, i = 0; numColons < 3 && i < input.length(); ++i)
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
        auto val = input.at(0);
        input.remove(0, 1);
        return new BarrelString{val, *this};
    }
}

// TODO: this contains a lot of stuff that is duplicated; it'd be nice to move everything here back
// into getInstructionNode (this should be feasable, although it could make for some fascinating
// runtime and/or logic errors)
InstructionNode *BarrelParser::getNumberNode(QString &input)
{
    if (input[0] == 'a')
    {
        input.remove(0, 1);
        return new AccumulatorAccessor{*this};
    }
    else if (input[0] == L'∞')
    {
        input.remove(0, 1);
        return new Infinity{*this};
    }
    else if (input[0] == '@')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new RegisterAccessor{number, *this};
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
        return new EqualTo{number, *this};
    }
    else if (input[0] == L'≈')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new FuzzyEqualTo{number, *this};
    }
    else if (input[0] == L'≠')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new NotEqualTo{number, *this};
    }
    else if (input[0] == L'≉')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new FuzzyNotEqualTo{number, *this};
    }
    else if (input[0] == '>')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new GreaterThan{number, *this};
    }
    else if (input[0] == '<')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new LessThan{number, *this};
    }
    else if (input[0] == L'≥')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new GreaterThanEqualTo{number, *this};
    }
    else if (input[0] == L'≤')
    {
        input.remove(0, 1);
        auto number = getNumberNode(input);
        return new LessThanEqualTo{number, *this};
    }
    else if (m_numericShortcuts.keys().contains(input.at(0)))
    {
        auto num = input.at(0);
        input.remove(0, 1);
        return new Number{m_numericShortcuts.value(num), *this};
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
        auto val = input.at(0);
        input.remove(0, 1);
        // return the char's codepoint
        return new Number{static_cast<double>(val.toLatin1()), *this};
    }

    input.remove(0, numString.length());
    return new Number{numString.toDouble(), *this};
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

double BarrelParser::getInput()
{
    double d = 0;

    if (m_hasOutputThisRound) // get off the line with output
    {
        std::cout << "\n";
    }
    std::cout << ": ";
    std::cin >> d;

    if (std::cin.fail())
    {
        std::cin.clear();
        d = static_cast<double>(std::cin.get());
    }

    // clear the input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return d;
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
