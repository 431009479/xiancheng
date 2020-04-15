/*************************************************************************
	> File Name: showShell.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月12日 星期日 20时20分12秒
 ************************************************************************/

    	/* 终端提示符组成：[用户名+@+主机名+当前目录]+用户提示符 */
#include "head.h"

void showShell(void){
	uid_t uid;
	char *ret, *sub;
	struct  passwd *user;
	char hostname[100];
    char buff[50] = {0};
	char cwd[120];
	uid = getuid();     /* 获取用户id */
    /* 根据uid获取用户的passwd结构体 */
	user = getpwuid(uid);
	printf("[%s@",user->pw_name); // 打印用户名

	/* 获取主机名 */
	gethostname(hostname, 100);
    strncpy(buff, hostname, 9);
	printf("%s ", buff);	  // 打印主机名
    /* 获取当前工作目录 */
	getcwd(cwd, 120);
	if (strcmp(cwd,user->pw_dir) == 0){
		printf("~]"); 			  // 家目录特殊处理
	}else{
		ret = strrchr(cwd,'/');   // 获取路径的最后一个目录
		if (ret[1] == '\0'){
			printf("/]");		  // 根目录
		}else{
			printf("%s]",ret+1);
		}
	}
    /* 打印用户提示符 */
	if (0 == uid){
		printf("# ");		// 超级用户
	}else{
		printf("$ ");		// 普通用户
	}
    fflush(stdout);			
}

