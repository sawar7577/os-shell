#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <linux/rtc.h>

int tokenize(char **arr, char *command, char *token)
{
    memset(arr,0,sizeof(arr));
    char *cm = strtok(command,token);
    int tokens = 0;
    while(cm != NULL)
    {
        arr[tokens++] = cm;
        cm = strtok(NULL,token);
    }
    return tokens;
}