#include "../include/cpu.h"
#include "../include/screen.h"
#include "lib/arrays.h"
#include <stdio.h>
#include "lib/instruction.h"

ptr_array *read_from_file(const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (!file)
  {
    perror("Failed to open file");
    return NULL;
  }

  ptr_array *result = ptr_array_new();
  int value;
  while (fread(&value, sizeof(int), 1, file) == 1)
  {
    instruction *inst = instruction_decode(value);
    ptr_array_push(result, value);
  }

  fclose(file);
  return result;
}

int main()
{
  ptr_array *ops = read_from_file("../assembler/test.bin");
  cpu *cpu = cpu_create();
  cpu_start(cpu);
  int running = 1;
  for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
  {
    cpu_write_mem(cpu, 0x00010000 + i, 0xFF0000ff);
  }
  for (int i = 0; i < ops->size; i++)
  {
    cpu_write_mem(cpu, i, ptr_array_get(ops, i));
  }
  printf("test3\n");
  cpu_vram_to_screen(cpu);
  cpu_run(cpu);
  cpu_free(cpu);
}
