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
#include <signal.h>


int main()
{
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN); 

    gethostname(host_name,PATH_MAXSIZE);
    getlogin_r(login_name,PATH_MAXSIZE);
    getcwd(home_dir,PATH_MAXSIZE);
    char command[PATH_MAXSIZE];
    while(1)
    {
        memset(command,0,sizeof(command));
        signal(SIGCHLD,child_signal_handler);
        print_prompt();
        scanf("%[^\n]s",command);
        getchar();
        execute_command(command);
    }
    return 0;
}