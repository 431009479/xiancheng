/*************************************************************************
	> File Name: mmap.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月13日 星期一 22时04分50秒
 ************************************************************************/

#include<stdio.h>
#include<sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int len, ret;
    char *p = NULL;
    int fd = open("./my_mmap.txt", O_CREAT|O_RDWR, 0644);
    if(fd  < 0){
        perror("open");
        return 1;
    }
    len = ftruncate(fd, 4);
    if(len == -1){
        perror("ftruncate");
        return 1;
    }
    p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap");
        return 1;
    }
    strcpy(p,"123\n");
    ret = munmap(p, 4);
    if(ret == -1){
        perror("mumap");
        return 1;
    }
    close(fd);


    return 0;
}
