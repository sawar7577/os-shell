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
#include "headers.h"


void pwd(char **arr)
{
    char *cur_dir = (char *)malloc(PATH_MAXSIZE*sizeof(char));
    getcwd(cur_dir,PATH_MAXSIZE);
    printf("%s\n",cur_dir);
}