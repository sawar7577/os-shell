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

void print_prompt()
{
    char *cur_dir = (char *)malloc(PATH_MAXSIZE*sizeof(char));

    getcwd(cur_dir,PATH_MAXSIZE);

    int len_home_dir = strlen(home_dir);
    int len_cur_dir = strlen(cur_dir);
    
    if(len_home_dir <= len_cur_dir)
    {
        memmove(cur_dir, cur_dir+len_home_dir, len_cur_dir-len_home_dir+1);
        printf("\033[32;1m<%s@%s:~%s>\033[0m",login_name,host_name,cur_dir);
    }
    else
    {
        printf("\033[32;1m<%s@%s:%s>\033[0m",login_name,host_name,cur_dir);
    }

    free(cur_dir);
    return;
}