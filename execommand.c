#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void execute_command(char *command)
{
    char *arr[50];
    char *token = (char *)malloc(sizeof(char)*10);
    memset(token,0,sizeof(token));
    token[0] = ';';
    token[1] = '\0';
    tokenize(arr,command,token);
    for(int i = 0 ; arr[i]!=NULL; ++i)
    {
        char *commands[50];
        memset(commands,0,sizeof(commands));
        memset(token,0,sizeof(token));
        token[0] = '|';
        token[1] = '\0';
        tokenize(commands,arr[i],token);
        int pipes[2];
        int ffd = 0;
        for(int j = 0; commands[j]!=NULL; ++j)
        {       
            pipe(pipes);
            char *args[50];
            memset(args,0,sizeof(args));
            memset(token,0,sizeof(token));
            token[0] = ' ';
            token[1] = '\t';
            token[2] = '\0';
            
            int words = tokenize(args,commands[j],token);
            if(commands[1] == NULL){
                individual_commands(args,words);
            }else{
                int pid = fork();
                if(pid == 0)
                {
                    dup2(ffd,0);
                    close(pipes[0]);

                    if(commands[j+1]!=NULL)
                    {
                        dup2(pipes[1],1);
                    }
                    individual_commands(args,words);
                    exit(0);
                }
                else{
                    wait(NULL);
                    ffd = pipes[0];
                    close(pipes[1]);
                }
            }
            
        }
    }
    return;
}


void individual_commands(char **args, int words)
{
    int fd;
    char inpfile[1000], outfile[1000], appendfile[1000];
    int inpflag = 0;
    int outflag = 0;
    int appendflag = 0;
    int outfd = dup(1);
    int infd = dup(0);
    for(int j=0 ;args[j]!=NULL; ++j)
    {
        if(strcmp(args[j],"<") == 0)
        {
            inpflag = 1;
            args[j] = NULL;
            strcpy(inpfile,args[j+1]);
        }
        else if(strcmp(args[j],">") == 0)
        {
            outflag = 1;
            args[j] = NULL;
            strcpy(outfile,args[j+1]);
        }
        else if(strcmp(args[j],">>") == 0)
        {
            appendflag = 1;
            args[j] = NULL;
            strcpy(appendfile,args[j+1]);
        }
    }
    
    if(inpflag)
    {
        fd = open(inpfile,O_RDONLY, 0);
        if(fd < 0)
        {
            printf("Error opening file %s\n",inpfile);
        }
        if(dup2(fd,0) < 0)
        {
            printf("Error in duping\n");
        }
        close(fd);
    }
    if(outflag)
    {
        fd = open(outfile,O_WRONLY | O_TRUNC | O_CREAT ,0644);
        if(fd < 0)
        {
            printf("Error opening file %s\n",outfile);
        }
        if(dup2(fd,1) < 0)
        {
            printf("Error in duping\n");
        }
        close(fd);
    }
    if(appendflag)
    {
        fd = open(appendfile,O_WRONLY | O_APPEND | O_CREAT ,0644);
        if(fd < 0)
        {
            printf("Error opening file %s\n",appendfile);
        }
        if(dup2(fd,1) < 0)
        {
            printf("Error in duping\n");
        }
        close(fd);
    }

    if(args[0]==NULL)
    {
        return;
    }

    if(strcmp(args[0],"cd") == 0)
    {
        cd(args,words);
    }
    else if(strcmp(args[0],"pwd") == 0)
    {
        pwd(args);
    }
    else if(strcmp(args[0],"echo") == 0)
    {
        echo(args,words);
    }
    else if(strcmp(args[0],"ls") == 0)
    {
        ls(args,words);
    }
    else if(strcmp(args[0],"pinfo") == 0)
    {
        pinfo(args,words);
    }
    else if(strcmp(args[0],"quit") == 0)
    {
        exit(0);
    }
    else if(strcmp(args[0],"remindme") == 0)
    {
        remindme(args,words);
    }
    else if(strcmp(args[0],"clock") == 0)
    {
        clck(args,words);
    }
    else if(strcmp(args[0],"setenv") == 0)
    {
        setenvvar(args,words);
    }
    else if(strcmp(args[0],"unsetenv") == 0)
    {
        unsetenvvar(args,words);
    }
    else if(strcmp(args[0],"kjob") == 0)
    {
        kjob(args,words);
    }
    else if(strcmp(args[0],"jobs") == 0)
    {
        jobs(args,words);
    }
    else if(strcmp(args[0],"overkill") == 0)
    {
        overkill(args,words);
    }
    else if(strcmp(args[0],"bg") == 0)
    {
        bg(args,words);
    }
    else if(strcmp(args[0],"fg") == 0)
    {
        fg(args,words);
    }
    else
    {
        other_commands(args,words);
    }
    dup2(outfd,1);
    close(outfd);
    dup2(infd,0);
    close(infd);
}

      // printf("%d\n",words);
            // int words = 0;
            // char *cm = strtok(arr[i], " \t");
            // if(cm == NULL)
            // {
                // continue;
            // }
            // while(cm != NULL)
            // {
                // args[words++] = cm;
                // cm = strtok(NULL, " \t");
            // }
