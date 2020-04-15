/*************************************************************************
	> File Name: shell.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月12日 星期日 21时57分28秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/showShell.h"

#define SIZE 1024

int main(){
    
    char buff[SIZE] = {0};
    pid_t pid;


    while(1){
        showShell();
        scanf("%[^\n]s", buff);
        getchar();
        if(strncmp(buff,"cd",2) == 0){
            My_Cd(buff);
            continue;
        }else if(strncmp(buff, "exit", 4) == 0){
            printf("\n");
            exit(0);
        }if((pid = fork()) < 0){
            perror("fork");
            return 0;
        }
        if(pid == 0) {
            execlp("sh", "sh", "-c", buff, NULL);
        } 
        wait(0);
    }

    return 0;
}
