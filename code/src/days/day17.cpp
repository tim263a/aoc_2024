#include "days/day17.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

Day17::Day17()
    : m_buffer(256)
{

}

template<typename Iter>
static uint64_t readNumber(Iter& it)
{
    uint64_t number = 0;

    for (; *it >= '0' && *it <= '9'; it++)
    {
        number *= 10;
        number += *it - '0';
    }

    return number;
}


void Day17::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    auto it = m_buffer.cbegin();

    it += 12;
    m_regA = readNumber(it);
    it += 13;
    m_regB = readNumber(it);
    it += 13;
    m_regC = readNumber(it);

    it += 11;
    for (; *it != '\0'; it += 2)
    {
        m_opCodes.push_back(*it -  '0');
    }
}

int64_t Day17::getComboOperand(uint8_t opCode)
{
    switch (opCode)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return opCode;
        case 4:
            return m_regA;
        case 5:
            return m_regB;
        case 6:
            return m_regC;
        default:
        case 7:
            printFmt("Invalid operand {}\n", opCode);
            std::abort();
    }
}

uint64_t Day17::calculatePart1()
{
    uint64_t sum = 0;

    std::vector<int64_t> output;

    uint64_t ip = 0;

    while (ip <= m_opCodes.size())
    {
        uint8_t opCode = m_opCodes[ip];
        uint8_t operand = m_opCodes[ip + 1];

        printFmt("ip {:2} opCode {:1} operand {:1} regA {:10} regB {:10} regC {:10}\n",
            ip, opCode, operand, m_regA, m_regB, m_regC);

        switch (opCode)
        {
            case 0:
                // adv instruction performs division.
                // The numerator is the value in the A register.
                // The denominator is found by raising 2 to the power of the instruction's combo operand.
                // (So, an operand of 2 would divide A by 4 (2^2); an operand of 5 would divide A by 2^B.)
                // The result of the division operation is truncated to an integer and then written to the A register.

                m_regA >>= getComboOperand(operand);
                ip += 2;
            break;
            case 1:
                // bxl instruction calculates the bitwise XOR of register B and the instruction's literal operand, then stores the result in register B.

                m_regB = m_regB ^ operand;
                ip += 2;
            break;
            case 2:
                // bst instruction calculates the value of its combo operand modulo 8 (thereby keeping only its lowest 3 bits), then writes that value to the B register.
                m_regB = getComboOperand(operand) % 8;
                ip += 2;
            break;
            case 3:
                // jnz instruction does nothing if the A register is 0.
                // However, if the A register is not zero, it jumps by setting the instruction pointer to the value of its literal operand; if this instruction jumps, the instruction pointer is not increased by 2 after this instruction.

                if (m_regA)
                {
                    ip = operand;
                }
                else
                {
                    ip += 2;
                }
            break;
            case 4:
                // bxc instruction calculates the bitwise XOR of register B and register C, then stores the result in register B.
                // (For legacy reasons, this instruction reads an operand but ignores it.)

                m_regB = m_regB ^ m_regC;
                ip += 2;
            break;
            case 5:
                // out instruction calculates the value of its combo operand modulo 8, then outputs that value.
                // (If a program outputs multiple values, they are separated by commas.)

                output.push_back(getComboOperand(operand) % 8);
                ip += 2;
            break;
            case 6:
                // bdv instruction works exactly like the adv instruction except that the result is stored in the B register.
                // (The numerator is still read from the A register.)

                m_regB = m_regA >> getComboOperand(operand);
                ip += 2;
            break;
            case 7:
                // cdv instruction works exactly like the adv instruction except that the result is stored in the C register.
                // (The numerator is still read from the A register.)

                m_regC = m_regA >> getComboOperand(operand);
                ip += 2;
            break;
            default:
                printFmt("Unknown opCode {}\n", opCode);
        }
    }

    printFmt("Ouput: ");
    for (auto out : output)
    {
        printFmt("{},", out);
    }
    printFmt("\n");

    return sum;
}

uint64_t Day17::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
