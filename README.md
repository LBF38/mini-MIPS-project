# mini-MIPS Project

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/lbf38/mini-MIPS-project?style=plastic)](https://github.com/lbf38/mini-MIPS-project/releases/latest)

**README available in the following languages :**

[![English documentation (en_US)](https://img.shields.io/badge/-en__US-blueviolet)](https://github.com/lbf38/mini-MIPS-project/README.md)
[![French documentation (fr_FR)](https://img.shields.io/badge/-fr__FR-blueviolet)](https://github.com/lbf38/mini-MIPS-project/README_fr_FR.md)

## Table of contents

- [mini-MIPS Project](#mini-mips-project)
  - [Table of contents](#table-of-contents)
  - [Short explanation of this project](#short-explanation-of-this-project)
  - [Installation](#installation)
  - [Usage](#usage)
    - [Assembleur](#assembleur)
    - [Virtual Machine](#virtual-machine)
  - [Demonstration](#demonstration)
  - [A list of simple examples](#a-list-of-simple-examples)
  - [Ideas](#ideas)
  - [Ressources](#ressources)
  - [Credits](#credits)

*****

## Short explanation of this project

This project is an academic project during the second year of study at ENSTA Bretagne (Brest, France).

It aims to reproduce a simple version of the MIPS architecture (therefore the name "mini-MIPS") in order to understand the functioning of a computer and its internal architecture.

It is composed of a virtual machine (VM) and an assembler.
The first one is written in C and the second one in Python.

## Installation

1. To install the project, please clone this repository in a Linux environnement. You can use the following command :

    ```bash
    git clone https://github.com/LBF38/mini-MIPS-project.git
    ```

2. Then, you can go to the corresponding folder in your terminal and use the following command to compile the VM :

    ```bash
    make
    ```

3. You can now use the VM and the assembler.

## Usage

### Assembleur

To launch the assembler, use the format :

```bash
./src/assembleur.py [folder/source.txt] [folder/destination.bin]
```

>**Note:** This command is executed in the project folder, for example under Linux : `~/mini-MIPS-project$`

Example :

```bash
./src/assembleur.py data/asm.txt bin/asm.bin
```

> If you don't specify the name of the destination file, by default the assembler will write in `bin/[source name].bin`

### Virtual Machine

To launch the VM, use the format :

```bash
./bin/vm bin/[source].bin
```

Example :

```bash
./bin/vm bin/asm.bin
```

> **Note:** You can compile the VM files (which is in C) with the makefile using `make`

## Demonstration

To demonstrate the use of the assembler and the VM, you can find some examples of assembly code in the `data/` folder.

This files respect the semantic chosen for the basic instructions of the VM. You can find it in the file [instructions.md](docs/instructions.md).

## A list of simple examples

Je vais vous présenter les fichiers d'exemples que vous pouvez trouver dans le dossier `data/`, en vous donnant une courte explication de leur fonctionnement.

In this part, I will present the files that you can find in the `data/` folder, giving you a short explanation of their functioning.

- `asm.txt` : This file contains an example of assembly code. It is used to demonstrate the use of the assembler. It allows to test the comments, the basic instructions, the labels and the empty lines.
- `affiche12.txt` : This file contains an example of assembly code to display 12 by performing a loop of 12 iterations.
- `factorial.txt` : This file contains an example of assembly code to display the factorial of a number. The user is asked for a value to calculate and we can thus calculate the associated factorial. We can ask for a value between 0 and 12.

> For this program, the limiting factor is the stack pointer which can be too low compared to the value requested by the user.
> We can see to improve this by calculating a larger stack pointer value depending on the value requested by the user and the maximum available memory.
>
> We are also limited by the representation of numbers. We cannot exceed 2^32-1 (4294967295) because we use a `uint32_t` to store the numbers.

- `fibonnaci.txt` : This file contains an example of assembly code to display the Fibonacci sequence. The code will ask the user for a value and the Fibonacci sequence will be calculated depending on this value.

> For this program, the limiting factor is the same as for `factorial.txt`: the representation of numbers will condition the maximum value available to calculate and display.

- `boucle.txt` : This file contains an example of assembly code to launch a loop and display its index.
- `helloworld.txt` : This file contains an example of assembly code to display "Hello World!".

> Note: `helloworld.txt` does not work for the moment because the data of type `string` are not yet recognized or treated by the assembler.

- `instruction_test.txt` : This file contains all the instructions available in my asm semantic. It allowed me to test all the functions one by one and to check their functioning, when I had implementation problems.

> A better method would have been to make unit tests directly on the assembler. I would implement them if I have the time. (see [#10](https://github.com/LBF38/projet_VM_archiNum/issues/10))

## Ideas

You will find here some ideas of programs to be made in assembly to test the assembler and the VM. These ideas come from the computer architecture course at ENSTA Bretagne and the ideas of the teachers.

- Calculate the points of the line $y = ax + b$ from the parameters provided by the user.
- Matrix calculation, matrix multiplication.
- Implementation of the Bresenham algorithm to draw a line. ([Bresenham algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm))
- Syracuse sequence. ([Syracuse sequence](https://en.wikipedia.org/wiki/Collatz_conjecture))

## Ressources

- Link to the article "VM in C" : [Register VM in C](https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C)
- Link to another ressource "LC-3 VM": [LC-3 VM](https://www.jmeiners.com/lc3-vm/index.html)

## Credits

This project was made by [Mathis URIEN (@LBF38)](https://github.com/lbf38), student in Design of Digital Sytems at ENSTA Bretagne.

The course and project was given by ENSTA Bretagne's professors.
