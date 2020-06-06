/*************************************************************************
	> File Name: b.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月04日 星期六 19时52分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

int main() {
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
  //memset(share_memory, 0,sizeof(struct Shm));
   // printf("%d\n",share_memory->pid);
    while(1){
        printf("<send> :");
        scanf("%[^\n]s",share_memory->buff);
        getchar();
        if(share_memory->pid == 0){
            printf("<Error> :服务端没上线!\n");
        }else{
            kill(share_memory->pid,SIGHUP);
//            kill(share_memory->pid,SIGUSR2);
        }
    }   
    return 0;
}
