/*-----------------------------------------------------------
Mini Shell (Custom Linux Shell)

Name        : Vaibhav Chavan
Project     : Mini Shell
Batch ID    : 25021_327
-------------------------------------------------------------

1. Introduction
The Mini Shell project is a simplified implementation of a UNIX/Linux shell.
It provides a command-line interface where the user can execute internal
commands, external commands, and manage processes similar to the bash shell.

The shell continuously displays a prompt, accepts user input, parses commands,
and executes them using system calls.

-------------------------------------------------------------
2. Features
1. Custom shell prompt display
2. Execution of external commands
3. Handling of internal commands (cd, pwd, exit, etc.)
4. Dynamic extraction of external commands
5. Continuous command execution loop
6. Modular and extensible design

-------------------------------------------------------------
3. Global Variables Used

char prompt[25];
char input_string[25];
char *ext_cmd[152];

Description:
1. prompt       -> Stores the shell prompt string
2. input_string -> Stores user input command
3. ext_cmd      -> Stores list of external commands dynamically allocated

-------------------------------------------------------------
4. Dynamic Memory Allocation
- Memory is allocated for 152 external command strings.
- Each command string is allocated 20 bytes.
- This allows storing multiple external command names safely.

-------------------------------------------------------------
5. Working Flow (main.c)

1. Clear the terminal screen
2. Initialize shell prompt
3. Allocate memory for external commands array
4. Extract all available external commands
5. Start infinite shell input loop
6. Accept user input and process commands

-------------------------------------------------------------
6. Function Used

extract_external_commands(ext_cmd)
- Reads and stores all available external commands
- Helps in validating and executing commands

scan_input(prompt, input_string)
- Displays prompt
- Reads user input
- Parses and executes commands continuously

-------------------------------------------------------------
7. Program Flow Diagram (Textual)

START
  |
  |--> Clear Screen
  |--> Initialize Prompt
  |--> Allocate Memory
  |--> Extract External Commands
  |--> Scan Input (Infinite Loop)
  |
 END (on exit command)

-------------------------------------------------------------
8. Advantages
1. Mimics real Linux shell behavior
2. Modular and readable code
3. Dynamic memory usage
4. Easy to extend with job control and signals
5. Strong use of system programming concepts

-------------------------------------------------------------
9. Conclusion
This Mini Shell implementation demonstrates a clear understanding of:
1. Process handling
2. Dynamic memory allocation
3. Command parsing
4. Modular C programming
5. UNIX/Linux system-level concepts

The main.c file acts as the control center of the shell, initializing
resources and invoking the command execution loop effectively.

-------------------------------------------------------------*/
#include "header.h"
char prompt[25];
char input_string[25];
char *ext_cmd[152];

int main()
{
    system("clear");
    char prompt[25] = "minishell$ :";
    char input_string[25];
    for (int i = 0; i < 152; i++)
    {
        ext_cmd[i] = malloc(20);
    }
    extract_external_commands(ext_cmd);
    scan_input(prompt,input_string);
    return 0;
}