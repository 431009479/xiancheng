/*************************************************************************
	> File Name: mmap.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月16日 星期四 19时28分09秒
 ************************************************************************/

#include<stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
    pid_t pid;
    int *a;
    int var = 0;
    a = mmap(0, 4, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    if((pid = fork()) < 0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        *a = 100;
        var = 10;
        printf("%d, %d\n", *a, var);

    }else{
        sleep(1);
        printf("%d, %d\n", *a, var);

    }
    
    return 0;
}
