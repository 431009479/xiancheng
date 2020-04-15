/*************************************************************************
	> File Name: pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月07日 星期二 23时03分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main() {
    pid_t pid;
    int pipefd[2];
    char buff[1024] = {0};
    if(pipe(pipefd) == -1){
        printf("NO\n");
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) { 
        while(1) {
            close(pipefd[0]);
            scanf("%[^\n]s", buff);
            getchar();
            write(pipefd[1], buff, sizeof(buff));
        }
    } else {
        while (1) {
            close(pipefd[1]);
            read(pipefd[0], buff, sizeof(buff));
            printf("server : %s\n", buff);
            memset(buff, 0, sizeof(buff));
        }
    }
    return 0;
}

