/*************************************************************************
	> File Name: b.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月05日 星期日 10时25分34秒
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



struct Msg {
	pthread_mutex_t muter;
    pthread_cond_t cond;
    char str[1024];
};
struct Msg *shm = NULL;

void do_add(){
    while(1){
    printf("After mutex lock\n");
    pthread_mutex_lock(&shm->muter);
    printf("Before mutex lock\n");
    pthread_cond_wait(&shm->cond, &shm->muter); 

    printf("After cond wait\n");
    printf("<Recv> : %s\n", shm->str);
    pthread_mutex_unlock(&shm->muter);    
    }
}


int main(int argc, char **argv) {
    
	key_t key = ftok(".", 233);
	int shmid;
    if ((shmid = shmget(key, sizeof(struct Msg), IPC_CREAT | 0666)) < 0) {
    perror("shmget");
    return 1;
}

if ((shm = (struct Msg *)shmat(shmid, NULL, 0)) < 0) {
    perror("shmat");
    return 1;
}
    memset(shm, 0, sizeof(struct Msg));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&shm->muter, &attr);


    pthread_condattr_t c_attr;
    pthread_condattr_init(&c_attr);
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&shm->cond, &c_attr);


    do_add();
    return 0;
}


