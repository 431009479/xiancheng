/*************************************************************************
	> File Name: cond_client.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月06日 星期一 09时47分43秒
 ************************************************************************/

#include<stdio.h>
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


int main(int argc, char **argv) {
    
	key_t key = ftok(".", 198);
	int shmid;
    if ((shmid = shmget(key, sizeof(struct Msg), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    if ((shm = (struct Msg *)shmat(shmid, NULL, 0)) < 0) {
        perror("shmat");
        return 1;
    }
    while(1){
        printf("Before muterx lock!\n");
        pthread_mutex_lock(&shm->muter);
        printf("<client> : ");
        scanf("%[^\n]s", shm->str);
        getchar();
        pthread_mutex_unlock(&shm->muter);

        pthread_cond_signal(&shm->cond); 
    }
    return 0;
}

