/*************************************************************************
	> File Name: Connect.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月28日 星期日 00时22分02秒
 ************************************************************************/

#include"Connect.h"

void catch_CHLD(int num)
{
	while(waitpid(-1,WNOHANG,NULL) > 0)
		;
}

void Zombury()
{
	signal(SIGCHLD,catch_CHLD);
}

pid_t CreateNewProc(Task task,...)
{
	va_list ap;
	pid_t pid;

	va_start(ap,task);

	pid = fork();
	if(0 == pid)
	{
		task(ap);
		exit(0);
	}

	return pid;
}

