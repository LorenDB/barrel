#include "PrimalityTest.h"

PrimalityTest::PrimalityTest(InstructionNode *numberToTest, BarrelParser &parser)
    : InstructionNode{parser},
      m_numberToTest{numberToTest}
{
}

QVariant PrimalityTest::exec(ExecRole role)
{
    auto number = m_numberToTest->exec(NumericalValue);
    auto value = number.toDouble();

    for (int divisor = 2; divisor < value / 2 + 1; ++divisor)
        if (value / divisor == static_cast<int>(value / divisor))
            return {false};

    return {true};
}
