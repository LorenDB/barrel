#include "UnknownInstruction.h"

UnknownInstruction::UnknownInstruction(QChar instruction, BarrelParser &parser)
    : InstructionNode{parser},
      m_instruction{instruction}
{

}

QVariant UnknownInstruction::exec(ExecRole role)
{
    if (role == NumericalValue)
        return {static_cast<int>(m_instruction.toLatin1())};
    else
    {
        m_parser->print(m_instruction);
        return {};
    }
}
