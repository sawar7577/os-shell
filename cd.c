#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers.h"

void cd(char **arr, int words)
{
    int ret;
    if(words  > 2)
    {
        printf("too many arguments\n");
    }
    else if(words == 2)
    {
        if(strcmp(arr[1],"~") == 0)
        {
            ret = chdir(home_dir);
        }
        else
        {
            ret = chdir(arr[1]);
        }
    }
    else
    {
        ret = chdir(home_dir);
    }
    if(ret < 0)
    {
        printf("No such file or directory\n");
    }
    return;
}
