# MINI-SHELL-C

Project Description

MINI-SHELL-C is a custom Linux command-line shell implemented in C. The shell supports execution of built-in commands, external commands, command parsing, pipe handling, signal management, and basic job control similar to a Unix shell.

Detailed Description (for README)

MINI-SHELL-C is a simplified implementation of a Unix/Linux command interpreter written in C.
The shell continuously accepts user input, parses commands, identifies whether they are internal or external, and executes them using system calls such as fork(), execvp(), and waitpid().

The project demonstrates key Linux system programming concepts including process creation, signal handling, command parsing, and job management.

Features

Custom shell prompt

Built-in command execution

External command execution

Pipe (|) support

Background and foreground job control

Signal handling (Ctrl+C, Ctrl+Z)

Job management commands (jobs, fg, bg)

Dynamic loading of external commands

Modular design with multiple source files

Internal Commands Implemented

cd

pwd

exit

echo

jobs

fg

bg

These commands are handled directly inside the shell without creating a new process.

External Commands

External commands are dynamically loaded from a command list and executed using execvp() in a child process.

Examples:

ls

cat

grep

mkdir

rm

nano

Key System Programming Concepts Used

fork() for process creation

execvp() for command execution

waitpid() for process control

pipe() for command piping

dup2() for input/output redirection

signal() handling for job control

Dynamic memory allocation

Project Structure
MINI-SHELL-C
│
├── main.c
├── commands.c
├── scan_input.c
├── header.h
├── ext_cmd.txt
└── README.md
How to Compile
gcc main.c commands.c scan_input.c -o minishell
Run
./minishell
Example
minishell$ : ls
minishell$ : pwd
minishell$ : cd Desktop
minishell$ : ls | grep .c
Skills Demonstrated

Linux System Programming

Process Management

Command Parsing

Signal Handling

Job Control

Modular C Programming
