/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月05日 星期日 10时20分58秒
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
    pthread_mutex_lock(&shm->muter);
    
        scanf("%[^\n]s", shm->str);
        getchar();
    pthread_mutex_unlock(&shm->muter);

    pthread_cond_signal(&shm->cond); 
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

    do_add();
    return 0;
}

