# MINI-SHELL-C

## Overview

**MINI-SHELL-C** is a simplified Unix/Linux command-line shell implemented in **C**.
The shell provides a terminal interface where users can enter commands similar to a standard Linux shell. It parses user input, identifies whether the command is internal or external, and executes it using Linux system calls.

This project demonstrates important **Linux system programming concepts** such as process creation, command parsing, signal handling, and job control.

---

## Features

* Custom shell prompt
* Execution of built-in commands
* Execution of external Linux commands
* Pipe (`|`) support for command chaining
* Background and foreground job control
* Signal handling (`Ctrl + C`, `Ctrl + Z`)
* Job management commands (`jobs`, `fg`, `bg`)
* Dynamic loading of external commands
* Modular C programming structure

---

## Built-in Commands

The shell supports several built-in commands executed internally without creating a new process.

Examples:

* `cd` – Change directory
* `pwd` – Print current working directory
* `exit` – Exit the shell
* `echo` – Display text or environment values
* `jobs` – Show stopped jobs
* `fg` – Bring a job to foreground
* `bg` – Resume a stopped job in background

---

## External Commands

External commands are executed using `fork()` and `execvp()` system calls.

Examples:

* `ls`
* `cat`
* `grep`
* `mkdir`
* `rm`
* `nano`
* `ping`

---

## System Programming Concepts Used

This project demonstrates the use of important **Linux system calls and concepts**:

* `fork()` – Process creation
* `execvp()` – Executing commands
* `waitpid()` – Process control
* `pipe()` – Inter-process communication
* `dup2()` – Input/Output redirection
* `signal()` – Signal handling
* Dynamic memory allocation (`malloc()`)

---

## Project Structure

```
MINI-SHELL-C
│
├── main.c
├── commands.c
├── scan_input.c
├── header.h
├── ext_cmd.txt
└── README.md
```

---

## How It Works

1. The shell displays a custom prompt.
2. The user enters a command.
3. The shell extracts the command name.
4. It checks whether the command is **internal or external**.
5. Internal commands are executed directly.
6. External commands are executed using `fork()` and `execvp()`.
7. The shell continues running until the `exit` command is issued.

---

## Compilation

Compile the project using **GCC**:

```bash
gcc main.c commands.c scan_input.c -o minishell
```

---

## Running the Shell

```bash
./minishell
```

---

## Example Usage

```
minishell$ : pwd
/home/user

minishell$ : ls

minishell$ : cd Documents

minishell$ : ls | grep .c
```

---

## Learning Outcomes

This project helps understand:

* Linux shell behavior
* Process management
* Signal handling
* Command parsing
* Job control mechanisms
* Modular system programming in C

---

## Author

**Nakul Anil Vadar**

Electronics and Telecommunications Engineer
Interested in **Embedded Systems, System Programming, and Linux Development**.
