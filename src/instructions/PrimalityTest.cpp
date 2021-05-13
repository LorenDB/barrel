#include "PrimalityTest.h"

PrimalityTest::PrimalityTest(InstructionNode *numberToTest, BarrelParser &parser)
    : InstructionNode{parser},
      m_numberToTest{numberToTest}
{
}

QVariant PrimalityTest::exec()
{
    auto number = m_numberToTest->exec();
    if (number.isValid())
    {
        auto value = number.toDouble();

        for (int divisor = 2; divisor < value / 2 + 1; ++divisor)
            if (value / divisor == static_cast<int>(value / divisor))
                return {false};

        return {true};
    }
    else
        return {}; // TODO: make this fail
}
