#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"
#include <sys/types.h>


void pinfo(char **args, int arguments)
{
    pid_t pid;
    char process_name[1000];  
    char process_path[1000];  
    if(arguments < 2)
    {
        pid = getpid();
        sprintf(process_name,"/proc/%d/stat",pid);
        sprintf(process_path,"/proc/%d/exe",pid);
    }
    else
    {
        pid = atoi(args[1]);
        sprintf(process_name,"/proc/%s/stat",args[1]);
        sprintf(process_path,"/proc/%s/exe",args[1]);
    }

    char memory_type[1000];
    char virtual_memory[1000];
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
    while(words != 23)
    {
        words++;
        fscanf(fp,"%s",virtual_memory);
    }

    printf("pid -- %d\n",(int)pid);
    printf("Process Status -- %s memory\n",memory_type);
    printf("- %s {Virtual Memory}\n",virtual_memory);
    fclose(fp);

    char exec_path[10000];
    int end = readlink(process_path,exec_path,256);
    exec_path[end]='\0';

    int len_home_dir = strlen(home_dir);
    int len_cur_dir = strlen(exec_path);
    
    if(len_home_dir <= len_cur_dir)
    {
        memmove(exec_path, exec_path+len_home_dir, len_cur_dir-len_home_dir+1);
        printf("Executable Path -- ~%s\n",exec_path);

    }
    else
    {
        printf("Executable Path -- %s\n",exec_path);
    }
}
