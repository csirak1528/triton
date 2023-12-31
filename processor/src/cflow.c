#include <stdio.h>

#include "../include/cpu.h"
#include "../include/execute.h"

bool cflow_execute(cpu *cpu, instruction *instruction)
{
  switch (instruction->opcode)
  {
  case JUMP:
  {
    word pc_value = cpu_read_reg(cpu, instruction->parameters.reg.r0);
    word pfg_value = cpu_read_reg(cpu, PFG_REG);
    cpu_write_reg(cpu, PC_REG, pc_value + pfg_value);
    break;
  }
  case JEQ:
  {
    word pfg_value = cpu_read_reg(cpu, PFG_REG);

    word pc_value = cpu_read_reg(cpu, instruction->parameters.reg.r0);
    word r1_value = cpu_read_reg(cpu, instruction->parameters.reg.r1);
    word r2_value = cpu_read_reg(cpu, instruction->parameters.reg.r2);
    if (r1_value == r2_value)
    {
      cpu_write_reg(cpu, PC_REG, pc_value + pfg_value);
    }
    break;
  }
  default:
    break;
  }
  return false;
}
