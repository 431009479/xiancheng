/*************************************************************************
	> File Name: Sadd.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月05日 星期日 16时33分10秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/file.h>
#include<pthread.h>
char num_file[] = "./.unm";


struct Shm {
	int now;
    int sum;
    pthread_mutex_t muter;
};

struct Shm *shm = NULL;


void do_add(int max, int x){
    while(1){
        pthread_mutex_lock(&shm->muter);
        if(shm->now > max){
            pthread_mutex_unlock(&shm->muter);
            break;
        }
        shm->sum += shm->now;
        shm->now++;
        printf("<%d> : <sum> :%d  <now> : %d\n", x, shm->sum, shm->now);
        pthread_mutex_unlock(&shm->muter);
    }
}

int main(int argc, char **argv) {
    if(argc != 3){
        fprintf(stderr, "Usade: %s max ins\n", argv[0]);
        return 1;
    }
    int x = 0;
    pid_t pid;
    int max = atoi(argv[1]);
    int ins = atoi(argv[2]);


	key_t key = ftok(".", 233);
	int shmid;
    if ((shmid = shmget(key, sizeof(struct Shm), IPC_CREAT | 0666)) < 0) {
         perror("shmget");
        return 1;
    }

    if ((shm = (struct Shm *)shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat");
        return 1;
    }
    shm->now = 0;
    shm->sum = 0;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
   // pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutexattr_setpshared(&attr, 1);
    pthread_mutex_init(&shm->muter, &attr);

    for(int i = 0; i < ins; i++){
        if((pid = fork()) < 0){
            perror("fork");
            return 1;
        }
        if(pid == 0){
            x = i;
            break;
        }
    }
    if(pid == 0){
        do_add(max, x);
        printf("<%d> exit!\n", x);
        exit(0);
    }
    while(ins){
        wait(NULL);
        ins--;
    }
    printf("Ans = %d\n", shm->sum);
    return 0;
}


