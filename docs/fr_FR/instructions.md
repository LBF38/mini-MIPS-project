# Instructions en assembleur et dans la VM

Voici une liste des instructions disponibles.

## Opérations arithmétiques et logiques

| OPCODE | Mnémonique     | Fonction                    | Sémantique       | Format |
|--------|----------------|-----------------------------|------------------|--------|
| 2      | add rd rs1 rs2 | addition                    | rd <= rs1 + rs2  | R      |
| 3      | add rd rs im   | addition                    | rd <= rs1 + im   | I      |
| 4      | sub rd rs1 rs2 | soustraction                | rd <= rs1 - rs2  | R      |
| 5      | sub rd rs im   | soustraction                | rd <= rs1 - im   | I      |
| 6      | mul rd rs1 rs2 | multiplication signée       | rd <= rs1 * rs2  | R      |
| 7      | mul rd rs im   | multiplication signee       | rd <= rs1 * im   | I      |
| 8      | div rd rs1 rs2 | division entiere signee     | rd <= rs1 / rs2  | R      |
| 9      | div rd rs im   | division entiere signee     | rd <= rs1 / im   | I      |
| 10     | and rd rs1 rs2 | ET logic bit a bit          | rd <= rs1 & rs2  | R      |
| 11     | and rd rs im   | ET logic bit a bit          | rd <= rs1 & im   | I      |
| 12     | or  rd rs1 rs2 | OU logic bit a bit          | rd <= rs1 \| rs2 | R      |
| 13     | or  rd rs im   | OU logic bit a bit          | rd <= rs1 \| im  | I      |
| 14     | xor rd rs1 rs2 | OU exclusif logic bit a bit | rd <= rs1 ^ rs2  | R      |
| 15     | xor rd rs im   | OU exclusif logic bit a bit | rd <= rs1 ^ im   | I      |
| 16     | shl rd rs1 rs2 | shift left                  | rd <= rs1 << rs2 | R      |
| 17     | shl rd rs im   | shift left                  | rd <= rs1 << im  | I      |
| 18     | shr rd rs1 rs2 | shift right                 | rd <= rs1 >> rs2 | R      |
| 19     | shr rd rs im   | shift right                 | rd <= rs1 >> im  | I      |

## Opérations de comparaison

| OPCODE | Mnémonique     | Fonction        | Sémantique                 | Format |
|--------|----------------|-----------------|----------------------------|--------|
| 20     | slt rd rs1 rs2 | set lower than  | rd <= (rs1 < rs2) ? 1 : 0  | R      |
| 21     | slt rd rs im   | set lower than  | rd <= (rs1 < im) ? 1 : 0   | I      |
| 22     | sle rd rs1 rs2 | set lower equal | rd <= (rs1 <= rs2) ? 1 : 0 | R      |
| 23     | sle rd rs im   | set lower equal | rd <= (rs1 <= im) ? 1 : 0  | I      |
| 24     | seq rd rs1 rs2 | set equal       | rd <= (rs1 = rs2) ? 1 : 0  | R      |
| 25     | seq rd rs im   | set equal       | rd <= (rs1 = im) ? 1 : 0   | I      |

## Load et Store

| OPCODE | Mnémonique         | Fonction         | Sémantique             | Format |
|--------|--------------------|------------------|------------------------|--------|
| 27     | load  rd ra offset | lecture memoire  | rd <= mem[ra + offset] | I      |
| 29     | store rs ra offset | ecriture memoire | mem[ra + offset] <= rs | I      |

## Branchements

| OPCODE | Mnémonique    | Fonction                | Sémantique                | Format |
|--------|---------------|-------------------------|---------------------------|--------|
| 30     | jmp   rd ra   | jump and link register  | rd <= PC ; PC <= ra       | JR     |
| 31     | jmp   rd addr | jump and link immediate | rd <= PC ; PC <= addr     | JI     |
| 32     | braz  rs addr | branch if zero          | if (rs = 0) {PC <= addr}  | B      |
| 33     | branz rs addr | branch if not zero      | if (rs != 0) {PC <= addr} | B      |

## Appels système

| OPCODE | Mnémonique | Fonction      | Sémantique                     | Format |
|--------|------------|---------------|--------------------------------|--------|
| 34     | scall n    | Appel systeme |                                | S      |
|        | scall 0    | Read number   | r20 <= number from keyboard    |        |
|        | scall 1    | Write number  | print r20 on screen            |        |
|        | scall 3    | Write char    | print r20 as a 7-bit character |        |
|        | scall 4    | Write string  | write string pointed to by r20 |        |

## Arrêt de la machine

| OPCODE | Mnémonique | Fonction             | Sémantique | Format |
|--------|------------|----------------------|------------|--------|
| 35     | stop       | Arrete le processeur |            | H      |
