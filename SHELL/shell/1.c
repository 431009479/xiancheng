/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月12日 星期日 23时47分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <utime.h>
#include <sys/signal.h>
char oldpwd[128] = {0};//记录上一次的路径
char *Argv[10]  = {0};

void type_prompt() {
	char hostname[256] = {'\0'};
	gethostname(hostname, sizeof(hostname));

	char curpath[256] = { '\0' };
	getcwd(curpath, 256);

	char prompt = '$';
	if (geteuid() == 0) {
		prompt = '#';
	}

	printf("%s@%s:%s%c", getpwuid(getuid())->pw_name, hostname,curpath, prompt);
}

void Cut_Cmd(char *cmd)
{
    int i = 0;
    memset(Argv,0,sizeof(Argv));
    char *p = strtok(cmd," ");
    while(p != NULL)
    {
        Argv[i++] = p;
        p = strtok(NULL," ");
    }
}

void My_Cd(char *cmd){
    char nowpath[128] = {0};
    getcwd(nowpath,127);
    char *p = cmd;
    while(*p != 0){
        if(*p == ' ' && *(p+1) != ' '){
            p++;
            break;
        }
        p++;
    }
    if(strlen(p) == 0 || strcmp(p,"~") == 0){
        struct passwd *pw = getpwuid(getuid());
        assert(pw != NULL);
        if(-1 == chdir(pw->pw_dir)){
            perror("cd : ");
            return;
        }
    }else if(strcmp(p,"-") == 0){
        if(strlen(oldpwd) == 0){
            printf("OLDPWD not set\n");
            return;
        }else{
            if(-1 == chdir(oldpwd)){
                perror("cd - : ");
                return;
            }
        }
    }else{
        if(-1 == chdir(p)){
            perror("cd : ");
            return;
        }
    }
    strcpy(oldpwd,nowpath);
}

void main(){
    while(1)
    {
        type_prompt();
        char cmd[128] = {0};
        fgets(cmd,128,stdin);
        cmd[strlen(cmd) - 1] = 0;//fgets

        if(strlen(cmd) == 0)
        {
            continue;
        }
        //cd  exit
        if(strncmp(cmd,"cd",2) == 0)
        {
            My_Cd(cmd);
            continue;
        }
        if(strncmp(cmd,"exit",4) == 0)
        {
            exit(0);
        }

        Cut_Cmd(cmd);

        pid_t n = fork();
        assert(n != -1);
        if(n == 0)
        {
           //execv
           char path[128] = "/home/mybin/";
           if(strstr(Argv[0],"/") != NULL)//判断 Argv have "/"
           {
               memset(path,0,128);
               strcpy(path,Argv[0]);
           }
           strcat(path,Argv[0]);
           execl("/bin/sh", "sh", "-c", *Argv, (char *) 0);
           //execv(Argv[0],Argv);
           perror("exec : ");
           exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
}

