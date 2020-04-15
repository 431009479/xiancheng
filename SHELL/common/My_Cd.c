/*************************************************************************
	> File Name: cd_shell.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月13日 星期一 00时09分32秒
 ************************************************************************/

#include "head.h"
char oldpwd[128] = {0};


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
        printf("..\n");
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
        printf("vfsbgvgfds\n");
        if(-1 == chdir(p)){
            perror("cd : ");
            return;
        }
    }
    strcpy(oldpwd,nowpath);
}

