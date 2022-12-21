# Instructions in assembler and in the VM

Here is a list of available instructions.

## Arithmetic and logical operations

| OPCODE | Mnemonic     | Function                    | Semantics       | Format |
|--------|----------------|-----------------------------|------------------|--------|
| 2      | add rd rs1 rs2 | addition                    | rd <= rs1 + rs2  | R      |
| 3      | add rd rs im   | addition                    | rd <= rs1 + im   | I      |
| 4      | sub rd rs1 rs2 | substraction                | rd <= rs1 - rs2  | R      |
| 5      | sub rd rs im   | substraction                | rd <= rs1 - im   | I      |
| 6      | mul rd rs1 rs2 | multiplication signed       | rd <= rs1 * rs2  | R      |
| 7      | mul rd rs im   | multiplication signed       | rd <= rs1 * im   | I      |
| 8      | div rd rs1 rs2 | signed integer division    | rd <= rs1 / rs2  | R      |
| 9      | div rd rs im   | signed integer division     | rd <= rs1 / im   | I      |
| 10     | and rd rs1 rs2 | logical bitwise AND         | rd <= rs1 & rs2  | R      |
| 11     | and rd rs im   | logical bitwise AND         | rd <= rs1 & im   | I      |
| 12     | or  rd rs1 rs2 | logical bitwise OR          | rd <= rs1 \| rs2 | R      |
| 13     | or  rd rs im   | logical bitwise OR          | rd <= rs1 \| im  | I      |
| 14     | xor rd rs1 rs2 | exclusive logical bitwise OR | rd <= rs1 ^ rs2  | R      |
| 15     | xor rd rs im   | exclusive logical bitwise OR | rd <= rs1 ^ im   | I      |
| 16     | shl rd rs1 rs2 | shift left                  | rd <= rs1 << rs2 | R      |
| 17     | shl rd rs im   | shift left                  | rd <= rs1 << im  | I      |
| 18     | shr rd rs1 rs2 | shift right                 | rd <= rs1 >> rs2 | R      |
| 19     | shr rd rs im   | shift right                 | rd <= rs1 >> im  | I      |

## Comparison operations

| OPCODE | Mnemonic     | Function        | Semantics                 | Format |
|--------|----------------|-----------------|----------------------------|--------|
| 20     | slt rd rs1 rs2 | set lower than  | rd <= (rs1 < rs2) ? 1 : 0  | R      |
| 21     | slt rd rs im   | set lower than  | rd <= (rs1 < im) ? 1 : 0   | I      |
| 22     | sle rd rs1 rs2 | set lower equal | rd <= (rs1 <= rs2) ? 1 : 0 | R      |
| 23     | sle rd rs im   | set lower equal | rd <= (rs1 <= im) ? 1 : 0  | I      |
| 24     | seq rd rs1 rs2 | set equal       | rd <= (rs1 = rs2) ? 1 : 0  | R      |
| 25     | seq rd rs im   | set equal       | rd <= (rs1 = im) ? 1 : 0   | I      |

## Load and Store

| OPCODE | Mnemonic         | Function         | Semantics             | Format |
|--------|--------------------|------------------|------------------------|--------|
| 27     | load  rd ra offset | read memory  | rd <= mem[ra + offset] | I      |
| 29     | store rs ra offset | write memory | mem[ra + offset] <= rs | I      |

## Connections

| OPCODE | Mnemonic    | Function                | Semantics                | Format |
|--------|---------------|-------------------------|---------------------------|--------|
| 30     | jmp   rd ra   | jump and link register  | rd <= PC ; PC <= ra       | JR     |
| 31     | jmp   rd addr | jump and link immediate | rd <= PC ; PC <= addr     | JI     |
| 32     | braz  rs addr | branch if zero          | if (rs = 0) {PC <= addr}  | B      |
| 33     | branz rs addr | branch if not zero      | if (rs != 0) {PC <= addr} | B      |

## System calls

| OPCODE | Mnemonic | Function      | Semantics                     | Format |
|--------|------------|---------------|--------------------------------|--------|
| 34     | scall n    | System call |                                | S      |
|        | scall 0    | Read number   | r20 <= number from keyboard    |        |
|        | scall 1    | Write number  | print r20 on screen            |        |
|        | scall 3    | Write char    | print r20 as a 7-bit character |        |
|        | scall 4    | Write string  | write string pointed to by r20 |        |

## Stop the machine

| OPCODE | Mnemonic | Function             | Semantics | Format |
|--------|------------|----------------------|------------|--------|
| 35     | stop       | Stop the processor |            | H      |
