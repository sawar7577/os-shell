#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers.h"


void remindme(char **arr, int arguments)
{
    int flag = 1;
    int pid = fork();
    int status;
    if(pid < 0)
    {
        printf("ERROR: forking child process failed\n");
    }
    else if(pid == 0)
    {
        sleep(atoi(arr[1]));
        printf("\n");
        for(int i = 2;arr[i]!=NULL;++i)
        {
            printf("%s ",arr[i]);
        }
        exit(1);
    }
    return;
}