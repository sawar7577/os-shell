#include <signal.h>
#include "headers.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int flagc, flagz;


void kjob(char ** args, int arguments)
{
    if(arguments < 3){
        printf("MISSING arguments\n");
        return;
    }
    int status;
    int cnt = 0;
    for(int i=0; i<100001;++i )
    {
        if(proc_names[i]!=NULL)
        {
            cnt++;
            if(cnt == atoi(args[1]))
            {
                kill(i,atoi(args[2]));
            }
        }
    }
}


void jobs(char ** args, int arguments)
{
    if(arguments > 1)
    {
        printf("Too many arguments\n");
    }
    int status;
    int cnt = 0;
    for(int i=0; i<100001;++i )
    {
        if(proc_names[i]!=NULL)
        {
            cnt++;
            pid_t pid = i;
            char process_name[1000];  
            // char process_path[1000];  
            sprintf(process_name,"/proc/%d/stat",pid);
            

            char memory_type[1000];
            // char virtual_memory[1000];
            int words = 0;
        
            FILE *fp = fopen(process_name,"r");
            if(fp == NULL)
            {
                printf("Error in opening %s\n",process_name);
                return;
            }
        
            while(words != 3)
            {
                words++;
                fscanf(fp,"%s",memory_type);
            }
            printf("[%d]\t",cnt);
            // printf("pid -- %d\n",(int)pid);
            // printf("%s ",memory_type);
            if(strcmp(memory_type,"T") == 0)
            {
                printf("STOPPED ");
            }
            else{
                printf("RUNNING ");
            }
            printf("%s[%d]\n",proc_names[i],i);
            // printf("- %s {Virtual Memory}\n",virtual_memory);
            fclose(fp);
        }
    }
}

void overkill(char ** args, int arguments)
{
    int status;
    int cnt = 0;
    for(int i=0; i<100001;++i )
    {
        if(proc_names[i]!=NULL)
        {
            proc_names[i]=NULL;
            cnt++;
            kill(i,SIGKILL);
            wait(NULL);
        }
    }
}

void bg(char **args, int arguments)
{
    if(arguments < 2)
    {
        printf("MISSING arguments\n");
        return;
    }
    int cnt = 0;
    for(int i=0; i<100001;++i )
    {
        if(proc_names[i]!=NULL)
        {
            cnt++;
            if(cnt == atoi(args[1]))
            {
                kill(i,SIGCONT);
            }
        }
    }
}

void fg(char **args, int arguments)
{
    int status;
    if(arguments < 2)
    {
        printf("MISSING arguments\n");
        return;
    }
    int cnt = 0;
    for(int i=0; i<100001;++i )
    {
        if(proc_names[i]!=NULL)
        {
            cnt++;
            if(cnt == atoi(args[1]))
            {
                kill(i,SIGCONT);
                int pid = i;
                flagc = 0;
                signal(SIGINT,CTRLC);
                flagz = 0;
                signal(SIGTSTP,CTRLZ);
                while(flagc == 0 && flagz == 0 && waitpid(pid, &status,WNOHANG)!=pid);

                if(flagz == 1){
                    setpgid(pid,pid);
                    kill(pid,SIGSTOP);
                    // proc_names[pid] = (char *)malloc(sizeof(proc_names[pid]));
                    // strcpy(proc_names[pid],proc_names[pid]);
                    signal(SIGCHLD,SIG_IGN);
                }
                if(flagc == 1){
                    // setpgid(pid,pid);
                    kill(pid,SIGKILL);
                    wait(NULL);

                }
                flagz = 0 ;
                flagc = 0 ;

                // waitpid(-1,&status,0);
                // proc_names[i] = NULL;
            }
        }
    }
}

void CTRLC(int arg)
{
    flagc = 1;
}

void CTRLZ(int arg)
{
    flagz = 1;
}