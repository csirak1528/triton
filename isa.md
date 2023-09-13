# Triton VM ISA

## Memory Layout

| Section      |           Address Range |
| :----------- | ----------------------: |
| Stack        | 0x00000000 - 0x00000FFF |
| Boot Sector  | 0x00001000 - 0x000011FF |
| Free Memory  | 0x00001200 - 0x0000FFFF |
| Video Memory | 0x00010000 - 0x0005AFFF |
| Free Memory  | 0x0005B000 - 0xFFFFFFFF |

## Registers

| Index | ABI Name | Name                    |
| ----: | -------: | :---------------------- |
|     0 |        z | Zero Register           |
|     1 |       ra | Return Address          |
|     2 |       sp | Stack Pointer           |
|     3 |       gp | Global Pointer          |
|     4 |       tp | Thread Pointer          |
|     5 |       pc | Program counter         |
|     6 |       fp | Frame pointer           |
|     7 |       fg | Operation flag register |
|  8-31 |  unnamed | Unnamed                 |

### Conventions:

r(n)\*: Any register (index of n)

r(n)!: Any register (index of n) that does not include:

- z
- ra
- sp
- gp
- tp
- fp
- fg

## Operations

### Math

| Instruction | Inputs          | Description              | Return Flags |
| :---------- | :-------------- | ------------------------ | ------------ |
| add         | r(0)!, r\*, r\* | r(0)! = r(1)\* + r(2)\*  |
| sub         | r(0)!, r\*, r\* | r(0)! = r(1)\* - r(2)\*  |
| mul         | r(0)!, r\*, r\* | r(0)! = r(1)\* \* r(2)\* |
| div         | r(0)!, r\*, r\* | r(0)! = r(1)\* / r(2)\*  |
| mod         | r(0)!, r\*, r\* | r(0)! = r(1)\* % r(2)\*  |
| sll         | r(0)!, r\*, r\* | r(0)! = r(1)\* << r(2)\* |
| srl         | r(0)!, r\*, r\* | r(0)! = r(1)\* >> r(2)\* |
| sra         | r(0)!, r\*, r\* | r(0)! = r(1)\* >> r(2)\* |
| and         | r(0)!, r\*, r\* | r(0)! = r(1)\* & r(2)\*  |
| or          | r(0)!, r\*, r\* | r(0)! = r(1)\* \| r(2)\* |
| xor         | r(0)!, r\*, r\* | r(0)! = r(1)\* ~ r(2)\*  |
| not         | r(0)!, r\*, r\* | r(0)! = r(1)\* ! r(2)\*  |
| slt         | r(0)!, r\*, r\* | r(0)! = r(1)\* < r(2)\*  |
| sltu        | r(0)!, r\*, r\* | r(0)! = r(1)\* < r(2)\*  |
| eq          | r(0)!, r\*, r\* | r(0)! = r(1)\* == r(2)\* |

### Control Flow

| Instruction | Inputs                 | Description                          |
| :---------- | :--------------------- | ------------------------------------ |
| jump        | r(0)\*                 | pc = r(0)\*                          |
| jeq         | r(0)\*, r(1)\*, r(2)\* | if r(1)\* == r(2)\* then jump r(0)\* |

[comment]: # "jeqz is a macro"

### Memory/Register Access

| Instruction | Inputs         | Description                          |
| :---------- | :------------- | ------------------------------------ |
| load        | r(0)!, r(1)\*  | r(0)! = memory[r(1)\*]               |
| str         | r(0)\*, r(1)\* | memory[r(0)\*] = r(1)\*              |
| setu        | r(0)!, imm     | r(0)! = imm << 16                    |
| setl        | r(0)!, imm     | r(0)! = imm                          |
| setr        | r(0)!, r(1)\*  | r(0)! = r(1)\*                       |
| irq         | r(0)\*         | interrupt request with code (r(0)\*) |
| syscall     | r(0)\*         | syscall with code (r(0)\*)           |

## Macros

### Control Flow

| Instruction | Inputs         | Description                       |
| :---------- | :------------- | --------------------------------- |
| jeqz        | r(0)\*, r(1)\* | if r(1)\* == 0\* then jump r(0)\* |

### Stack Access

| Instruction | Inputs | Description               |
| :---------- | :----- | ------------------------- |
| push        | r(0)\* | sp--; memory[sp] = r(0)\* |
| pop         | r(0)!  | r(0)\* = memory[sp]; sp++ |

| Errors           | Flag Register Value |
| :--------------- | ------------------: |
| Unknown Opcode   |                0x09 |
| Division By Zero |                0x69 |

## Instruction Encoding

Convention:
Parameter: |Type:Size in bits|

|Type:Size||Type:Size||Type:Size|

### Instruction types:

- 2 Paramter

  |Opcode:6| |r(0):6|

- 3 Paramter

  |Opcode:6| |r(0):6| |r(1):6|

- 4 Parameter

  |Opcode:6| |r(0):6| |r(1):6| |r(2):6|

- 3 Paramter Immediate

  |Opcode:6| |r(0):6| |imm: 16|