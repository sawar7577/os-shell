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


void ls(char **arr, int arguments)
{
    char *cur_dir = (char *)malloc(PATH_MAXSIZE*sizeof(char));
    getcwd(cur_dir,PATH_MAXSIZE);
    
    DIR *dir;
    char lmtime[100];
    struct dirent *file;
    struct stat stats;
    struct passwd *pw;
    struct group *gr;
    bool a_flag = false;
    bool l_flag = false;
    bool flag = false;  
    for(int i = 1; arr[i]!=NULL ; ++i)
    {
        if(strcmp(arr[i],"-l") == 0)
        {
            l_flag = true;
        }
        else if(strcmp(arr[i],"-a") == 0)
        {
            a_flag = true;
        }
        else if(strcmp(arr[i],"-la") == 0 || strcmp(arr[i],"-al") == 0)
        {
            l_flag = true;
            a_flag = true;
        }
    }
    dir = opendir(cur_dir);

    while((file = readdir(dir)) != NULL)
    {
        stat(file->d_name,&stats);
        pw = getpwuid(stats.st_uid);
        gr = getgrgid(stats.st_uid);
        if( ((strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0) && a_flag) || (strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0))
        {
            if(l_flag)
            {
                strftime(lmtime, 100, "%h %d %H:%M", localtime(&stats.st_ctime));        
                printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
                printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
                printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
                printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
                printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
                printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
                printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
                printf( (stats.st_mode & S_IROTH) ? "r" : "-");
                printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
                printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
                printf("\t%d",(int)stats.st_nlink);
                printf("\t%s",pw->pw_name);
                printf("\t%s",gr->gr_name);
                printf("\t%d",(int)stats.st_size);
                printf("\t%s",pw->pw_name);
                printf("\t%s\t",lmtime);
            }
            printf("%s\n",file->d_name);
        }

    }
    closedir(dir);
    return;
}
