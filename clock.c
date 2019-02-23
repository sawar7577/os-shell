#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"


void clck(char **args, int arguments)
{
    if(arguments < 5)
    {
        printf("***MISSING ARGUMENTS***\n");
        return ;
    }
    if(strcmp(args[1],"-t") || strcmp(args[3],"-n"))
    {
        printf("Incorrect flags\n");
        return;
    }
    int times = atoi(args[4])/atoi(args[2]) - 1;
    do
    {
            
            FILE *fp = fopen("/proc/driver/rtc","r");
            if(fp == NULL)
            {
                printf("***ERROR in opening FILE***\n");
                return;
            }
            char *line = NULL;
            char *line2 = NULL;
            size_t n = 0;
            
            getline(&line,&n,fp);
            n = 0;
            getline(&line2,&n,fp);
            
            char *cm = strtok(line2, " ");
            char tme[10000];
            
            memset(tme,0,sizeof(tme));
            while(cm != NULL)
            {
                strcpy(tme,cm);
                cm = strtok(NULL, " ");
            }
            tme[10] = '\0';
            printf("%s, ",tme);

            memset(tme,0,sizeof(tme));
            cm = strtok(line, " ");
            while(cm != NULL)
            {
                strcpy(tme,cm);
                cm = strtok(NULL, " ");
            }
            printf("%s",tme);

            fclose(fp);
            if(times < 0)
            {
                break;
            }
            sleep(atoi(args[2]));
    }while((times--)>=0);
    return;
}
