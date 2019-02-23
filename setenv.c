#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"

void setenvvar(char **args, int arguments)
{
    if(arguments < 2)
    {
        printf("Insufficient number of arguments\n");
    }
    if(arguments == 2)
    {
        if(setenv(args[1],"",1) != 0)
        {
            printf("ERROR in setting env variable\n");
        }
    }
    else if(setenv(args[1],args[2],1) != 0)
    {
        printf("ERROR in setting env variable\n");
    }
}

void unsetenvvar(char **args, int arguments)
{
    if(arguments < 2)
    {
        printf("Insufficient number of arguments\n");
    }
    if(unsetenv(args[1]) != 0)
    {
        printf("ERROR in deleting env variable\n");
    }
}