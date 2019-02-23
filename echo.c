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


void echo(char **arr, int words)
{
    for(int i = 1; arr[i]!=NULL ; ++i)
    {
        printf("%s ",arr[i]);
    }
    printf("\n");
    return;
}