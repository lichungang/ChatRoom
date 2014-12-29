/*************************************************************************
	> File Name: Connect.h
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月28日 星期日 00时05分52秒
 ************************************************************************/

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<signal.h>
#include<stdarg.h>
#include<netinet/in.h>

typedef void(*Task)(va_list);

pid_t CreateNewProc(Task task,...);
#endif
