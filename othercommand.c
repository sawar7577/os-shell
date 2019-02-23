#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"
#include <signal.h>

extern int flagz, flagc;

void other_commands(char **arr, int arguments)
{
    flagz = 0;
    flagc = 0;
    int flag = 1;
    if(arr[arguments-1]!=NULL && arr[arguments-1][0]=='&')
    {
        flag = 0;
        arr[arguments-1] = NULL;
    }
    int pid = fork();
    int status;
    if(pid == 0)
    {
        // signal(SIGCHLD,SIG_IGN);
        if(execvp(arr[0],arr) < 0)
        {
            printf("ERROR: exec failed\n");
            exit(1);
        }  
        // signal(SIGCHLD,SIG_IGN);

    }
    else if(pid < 0)
    {
        printf("ERROR: forking child process failed\n");
    }
    else
    {
        if(flag)
        {
            flagz = 0;
            signal(SIGTSTP,CTRLZ);
            flagc = 0;
            signal(SIGINT,CTRLC);
            while(flagc == 0 && flagz == 0 && waitpid(pid,&status,WNOHANG)!=pid);

            if(flagz == 1){
                setpgid(pid,pid);
                kill(pid,SIGSTOP);
                signal(SIGCHLD,SIG_IGN);
                proc_names[pid] = (char *)malloc(sizeof(arr[0]));
                strcpy(proc_names[pid],arr[0]);
            }
            if(flagc == 1){
                // setpgid(pid,pid);
                kill(pid,SIGKILL);
                wait(NULL);

            }
            flagz = 0 ;
            flagc = 0 ;

        }
        else
        {
            setpgid(pid,pid);
            proc_names[pid] = (char *)malloc(sizeof(arr[0]));
            strcpy(proc_names[pid],arr[0]);
            signal(SIGCHLD,SIG_IGN);
        }
    }
    return;
}
