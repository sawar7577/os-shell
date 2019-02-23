int flagz, flagc;

char *proc_names[100001];
#define PATH_MAXSIZE 10000
char home_dir[PATH_MAXSIZE], host_name[PATH_MAXSIZE], login_name[PATH_MAXSIZE];
void clck(char **args, int arguments);
void remindme(char **arr, int arguments);
int tokenize(char **arr, char *command, char *token);
void child_signal_handler();
void print_prompt();
void cd(char **arr, int words);
void pwd(char **arr);
void echo(char **arr, int words);
void other_commands(char **arr, int arguments);
void ls(char **arr, int arguments);
void execute_command(char *command);
void pinfo(char **args, int arguments);
void setenvvar(char **args, int arguments);
void unsetenvvar(char **args, int arguments);
void individual_commands(char **args, int words);
void kjob(char ** args, int arguments);
void jobs(char ** args, int arguments);
void overkill(char ** args, int arguments);
void bg(char **args, int arguments);
void fg(char **args, int arguments);
void CTRLC(int arg);
void CTRLZ(int arg);
