 #include "header.h"
 int pid = 0 , status;
 void scan_input(char *prompt,char *input_string)
 {
    signal(SIGINT,signal_handler);
    signal(SIGTSTP,signal_handler);

    while (1)
    {
        pid = 0;
        printf("%s ",prompt);

        scanf("%[^\n]",input_string);
        getchar();

        if(strncmp(input_string,"PS1=",4) == 0)
        {
            int space =0;
            for(int i =4; input_string[i] != '\0'; i++)
            {
                if(input_string[i] == ' '){
                    printf("invalid string\n");
                    space = 1;
                    break;
                }
            }
            if(!space){
                strcpy(prompt,input_string+4);
            }
        } 
        else{
            //get command.
            char *cmd = get_command(input_string);
            //check command type.
            int type = check_command_type(cmd);

            if(type == BUILTIN){
                execute_internal_commands(input_string);
            }
            else if(type == EXTERNAL)
            {
                pid = fork();
                if(pid > 0){
                    waitpid(pid,&status,WUNTRACED);

                }
                else if(pid == 0){

                    signal(SIGINT,SIG_DFL);
                    signal(SIGTSTP,SIG_DFL);

                    exe_Exeternal_commands(input_string);
                    
                }
            }
            else{
                printf("Erorr : NO command\n");
            }
        }
    }
}