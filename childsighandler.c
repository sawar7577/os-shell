#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

void child_signal_handler()
{
    int status;
    for(int i=0; i<100001;++i )
    {
        if(proc_names[i]!=NULL)
        {
            int ret = waitpid(i,&status,WNOHANG);
            if(ret)
            {
                printf("%s with pid %d exited normally\n",proc_names[i],i);
                free(proc_names[i]);
                proc_names[i]=NULL;
            }
            else if(ret == -1)
            {
                printf("*** ERROR in waitpid ***\n");
                return;
            }
                   
        }
    }
    return;
}