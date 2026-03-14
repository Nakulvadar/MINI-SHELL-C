#include "header.h"

stopped_jobs *head = NULL;

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","fg" , "bg" ,
						"jobs" , NULL};


						
 // check command function.
 char *get_command(char *input_string)
 {
    static char cmd[20];
    int  j =0;
    for(int i= 0;input_string[i] != '\0' && input_string[i] != ' ' ; i++)
    {
        cmd[j++] = input_string[i];
    }
    cmd[j] = '\0';
    return cmd;
 }

 //check type function.
 int check_command_type(char *command)
 {
    //check Internal command.
    for(int i =0;builtins[i] != NULL;i++){
        if(strcmp(builtins[i],command)==0){
            return BUILTIN;
        }
    }
    //check External command.
    for(int i =0 ; i < 152;i++){
        if(strcmp(ext_cmd[i],command)==0){
            return EXTERNAL;
        }
    }

    return NO_COMMAND;
 }

 // excute the internal command function.
 void execute_internal_commands(char *input_string)
 {

    char buffer[50];
    if(strcmp(input_string,"exit")==0){
        exit(0);
    }

    if(strcmp(input_string,"pwd")==0){
        getcwd(buffer,sizeof(buffer));
        printf("%s/",buffer);
    }
    if(strncmp(input_string,"cd",2)==0)
    {
        chdir(input_string+3);
        getcwd(buffer,sizeof(buffer));
        printf("%s\n",buffer);
    }
    else if(strcmp(input_string,"echo $$")==0){
        printf("%d \n",getpid());
    }
    else if(strcmp(input_string,"echo $?")==0){
        
        if(WIFEXITED(status)){
            printf("Noramal => %d\n",WEXITSTATUS(status));
        }
        else{
            printf("adnormal=> %d\n",WEXITSTATUS(status));
        }
    }
    else if(strcmp(input_string,"echo $SHELL")==0){
        printf("%s \n",getenv("SHELL"));
    }

    else if (strcmp(input_string, "jobs") == 0)
    {
        print_jobs(head);
    }
    else if(strcmp(input_string,"fg")==0){
         if (head != NULL)
        {
            // Resume the stopped process
            kill(head->pid, SIGCONT);
            pid = head->pid;

            // Print command being brought to foreground
            printf(ANSI_COLOR_CYAN "%s\n" ANSI_COLOR_RESET, head->sleep_command);

            // Wait for the process to finish or stop again
            waitpid(pid, &status, WUNTRACED);
            pid = 0;

            // Remove job from jobs list
            delete_jobs(&head);
        }
    }
      // Resume stopped job in background
    else if (strcmp(input_string, "bg") == 0)
    {
        if (head != NULL)
        {
            // Enable SIGCHLD handling for background job
            signal(SIGCHLD, signal_handler);

            // Resume the stopped process
            kill(head->pid, SIGCONT);

            // Print background job information
            printf(ANSI_COLOR_BLUE "[%d] %s &\n" ANSI_COLOR_RESET,
                   head->pid, head->sleep_command);

            // Remove job from jobs list
            delete_jobs(&head);
        }
        else
        {
            // No stopped job available
            printf(ANSI_COLOR_YELLOW "bg: no current job\n" ANSI_COLOR_RESET);
        }
    }
 }

 void extract_external_commands(char **external_commands)
 {
    
    int fd= open("ext_cmd.txt",O_RDONLY);
    if(fd == -1){
        printf("file not Open\n");
        return;
    }

    char ch;
    int i = 0, j=0;
    while (read(fd,&ch,1) > 0)
    {
        
        if(ch == '\n'){
             if (j > 0)
            {
                external_commands[i][j] = '\0';
                i++;
                j = 0;
            }
        }
        else{
            external_commands[i][j++] = ch;
        }
       
    }
    if (j > 0)
    {
        external_commands[i][j] = '\0';
    }

    close(fd);
 }

 //execute the external command.
void exe_Exeternal_commands(char *input_string)
{
    
    char *argv[100];
    int argc = 0, arg_j = 0;

    for (int i = 0; i < 100; i++)
    {
        argv[i] = malloc(50);
    }

    for (int i = 0; input_string[i] != '\0'; i++)
    {
        char ch = input_string[i];

        if (ch == ' ')
        {
            if (arg_j > 0)
            {
                argv[argc][arg_j] = '\0';
                argc++;
                arg_j = 0;
            }
        }
        else
        {
            argv[argc][arg_j++] = ch;
        }
    }

    if(arg_j > 0){
    argv[argc][arg_j++] = '\0';
        argc++;
    }

    argv[argc] = NULL; 
    int cmd[argc];
    
    int cmd_count =0 , pipe_c =0;

    cmd[cmd_count++] = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            argv[i] = NULL;
            cmd[cmd_count++] = i + 1;
            pipe_c = 1;
        }
    }
    if (pipe_c)
    {
        int pipe_fd1[2];

        for (int i = 0; i < cmd_count; i++)
        {
            int pid1;

            if (i < cmd_count - 1)
            {
                pipe(pipe_fd1);
            }

            pid1 = fork();

            if (pid1 > 0)   // parent
            {
                if (i < cmd_count - 1)
                {
                    close(pipe_fd1[1]);
                }
            }
            else if (pid1 == 0)  // child
            {
                if (i > 0)
                {
                    dup2(pipe_fd1[0], 0);
                }

                if (i < cmd_count - 1)
                {
                    dup2(pipe_fd1[1], 1);
                }

                close(pipe_fd1[0]);
                close(pipe_fd1[1]);

                execvp(argv[cmd[i]], argv + cmd[i]);
                perror("execvp");
                exit(1);
            }
        }

        while (wait(NULL) > 0);
        return;
    }
    else{
        execvp(argv[0],argv);
    }

}

//signal handler function.
 void signal_handler(int sig_num)
 {
    
    if(sig_num == SIGINT){
        

        if(pid == 0){
            printf("%s",prompt);
            fflush(stdout);
        }

    }
    
     // Handling Ctrl+Z signal
    if (sig_num == SIGTSTP)
    {
        if (pid == 0)
        {
            // Print prompt when no child is running
            printf(ANSI_COLOR_GREEN "\n%s " ANSI_COLOR_RESET, prompt);
            fflush(stdout);
        }
        else if (pid > 0)
        {
            // Insert stopped process into jobs list
            printf(ANSI_COLOR_YELLOW "\n" ANSI_COLOR_RESET);
            insert_jobs_at_start(&head);
        }
    }
    // Handling terminated background processes
    else if (sig_num == SIGCHLD)
    {
        waitpid(-1, &status, WNOHANG);
    }
}
    
// Function to print list of stopped jobs
void print_jobs(stopped_jobs *head)
{
    int i = 1;
    if(head == NULL){
        printf("No: jobs\n");
        return;
    }
    // Traverse and display each stopped job
    while (head)
    {
        printf(ANSI_COLOR_YELLOW "[%d]   Stopped                 %s\n"
               ANSI_COLOR_RESET, i++, head->sleep_command);
        head = head->next;
    }
}

// Function to insert a stopped job at the beginning of jobs list
void insert_jobs_at_start(stopped_jobs **head)
{
    // Allocate memory for new job node
    stopped_jobs *newNode = (stopped_jobs *)malloc(sizeof(stopped_jobs));

    if (newNode == NULL)
        return;

    // Store process details
    newNode->pid = pid;
    strcpy(newNode->sleep_command, input_string);
    newNode->next = NULL;

    // Insert node at the start of the list
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        newNode->next = *head;
        *head = newNode;
    }
}

// Function to delete the most recent job from jobs list
void delete_jobs(stopped_jobs **head)
{
    stopped_jobs *temp = *head;
    *head = temp->next;
    free(temp);
}