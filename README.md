## RUNNING

- run "make"

- execute by using "./Shell"

- type "exit" to exit the shell

## FEATURES

#### ls command
###### Usage:
- ls takes arguments as flags (in the form -(flagname)) and directories (in the form -(directory name)) in any order.
- It lists the files of all the directories mentioned, in the form of option selected by the flags.
- If there is no directory mentioned, it lists the files of current directory

* "ls" - lists the files and directories
* "ls -a" - display hidden files
* "ls -l" - long list
* "ls -al"/"ls -la"/"ls -l -a"/"ls -a -l" - long list including hidden files

- Similarities to real command: "ls -a" displays files sorted in alphabetical order (NOT CONSIDERING THE PREPENDED '.')  

#### cd command
* "cd (absolute path)" - goes to absolute path
* "cd" - goes to ~/
* "cd ~" - goes to ~/
* "cd .." - goes to previous directory
* "cd ." - goes to same directory

#### echo command
* "echo" - prints empty line
* "echo text" - prints "text"
* "echo 'text' " - prints "text"


#### pwd command
* "pwd" - prints absolute path of present working directory

#### pinfo command
* "pinfo" : prints the process related info of the shell program 
* "pinfo <pid>" : prints the process info about given pid
- pid -- 
- Process status -- {R/S/S+/Z}
- Virtual Memory
- Executable path -- (Absolute path - includes ~/ if executable is present inside the shell directory)

#### clock command
* "clock -t 'x' -n 'y'" : prints the dynamic date and time for 'y' duration in each 'x' intervals

#### remindme command
* "remindme 'time' 'text'" : displays the 'text' on the shell after 'time' duration. 