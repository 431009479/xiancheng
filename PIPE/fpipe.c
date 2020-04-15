/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月07日 星期二 23时34分28秒
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t pid;
    FILE *fp, *fp1;
    int pipefd[2];
    pipe(pipefd);
    char buff[1024] = {0};
    if ((pid = fork()) < 0) {
        perror("fork");
        return 1;
    }
    fp = fdopen(pipefd[1], "w");
    fp1 = fdopen(pipefd[0], "r");
    if (pid == 0) {
        while (1) {
           
            fgets(buff, sizeof(buff), stdin);
            fprintf(fp, "%s\n", buff);
            fflush(fp);
        }
    } else {
        while (1) {
            fgets(buff, sizeof(buff), fp1);
            printf("server : %s", buff);
        }
    }
    return 0;
}
