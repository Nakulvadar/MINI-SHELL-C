#ifndef HEADER_H
#define HEADER_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



 extern char *builtins[];
 extern char prompt[25];
 extern char input_string[25];
 extern int pid , status;
 extern char *ext_cmd[152];
// Head pointer for stopped jobs linked list
   
// Structure to maintain stopped jobs information
typedef struct list
{
    pid_t pid;
    char sleep_command[25];
    struct list *next;
    
} stopped_jobs;


void scan_input(char *prompt,char *input_string);

char *get_command(char *input_string);

int check_command_type(char *command);

void copy_change(char *prompt, char *input_string);

void echo(char *input_string, int status);

void execute_internal_commands(char *input_string);

void signal_handler(int sig_num);

void extract_external_commands(char **external_commands);

void exe_Exeternal_commands(char *input_string);

void insert_jobs_at_start(stopped_jobs **head);

void delete_jobs(stopped_jobs **head);

void print_jobs(stopped_jobs *head);

#endif