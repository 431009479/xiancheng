/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月04日 星期六 19时52分33秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<signal.h>

struct Shm{
    pid_t pid;
    char buff[1024];
};

struct Shm *share_memory = NULL;


void print(int sig) {
    printf("<parent> :%s\n",share_memory->buff);
}

int main() {
    pid_t pid;
    int shmid;
    key_t key = ftok(".", 198);//得到id
    
    if((shmid = shmget(key, sizeof(struct Shm), IPC_CREAT | 0666)) < 0) {
        //共享内存 所有人刻读可写
        perror("shmget");
        return 1;
    }
    

    if((share_memory = shmat(shmid, NULL, 0)) < 0){
        //真实的地址
        perror("shmat");
        return 1;
    }
    printf("After shmat!\n");
    share_memory->pid = getpid();
    while(1) {
       // share_memory->pid = getpid();
        signal(SIGHUP, print);
        //share_memory->pid = getpid();
        //signal(SIGUSR2, print);
        pause();
    }
    return 0;
}
