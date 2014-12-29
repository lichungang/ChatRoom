/*************************************************************************
	> File Name: server.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月28日 星期日 00时05分32秒
 ************************************************************************/

#include"Connect.h"

char *IP_ADDRESS = "127.0.0.1";
int IP_PORT = 9000;
int fds[100];
int size = 0;

int initServer()
{
	int socketFd;
	struct sockaddr_in addr;

	socketFd = socket(AF_INET,SOCK_STREAM,0);
	if(socketFd < 0)
	{
		perror("acqure socketFd error");
		return 0;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(IP_PORT);
	addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	int ret = bind(socketFd,(struct sockaddr *)&addr,sizeof(addr));
	if(ret < 0)
	{
		perror("bind error");
		return -1;
	}

	ret = listen(socketFd,10);
	if(ret < 0)
	{
		perror("listen error");
		return -2;
	}
	return socketFd;
}


void sendMsgToAll(char *msg)//给每个客户端发送消息
{
	int i;
	int ret;
	for(i = 0;i < size;i++)
	{
		if(fds[i] != 0)
		{
			printf("send to %d\n",fds[i]);			
			ret = send(fds[i],msg,strlen(msg),0);
			if(ret < 0)
			{
				perror("server send msg error");
				return ;
			}
		}
	}
}
void * service_thread(void *p)
{
	
	int ret;
	int fd = *(int *)p;
	int THID = pthread_self();
	char buf[100];

	printf("THID = [%d]\n",THID);
	printf("pthread = [%d]\n",fd);
	//一个客户端会开启服务器的一个线程,当一个线程开启是,将自己所对应的客户端的socketFd
	//发给其他的socketfd

	while(1)
	{
		int i;
		int ret;
		char buf[100] = {};
		ret = recv(fd,buf,sizeof(buf),0);

		if(ret <= 0)
		{
			printf("fd = [%d] quit\n",fd);
			for(i = 0; i < size;i++)
			{
				if(fd == fds[i])
				{
					fds[i] = 0;
					i = 0;
				}
			}
			printf("quit->fd = %d quit \n",fd);
			return ;
		}
		printf("recv : [%s]\n",buf);
		//群发
		sendMsgToAll(buf);
	}
}

void AcceptClient(va_list ap)
{
	int socketFd = va_arg(ap,int);

	printf("socketFd = [%d] pid = [%d]\n",socketFd,getpid());

	int clientFd;
	int len;
	struct sockaddr_in sockaddr;

	while(1)
	{
		char buf[80];
		len = sizeof(struct sockaddr_in);
		clientFd = accept(socketFd,(struct sockaddr *)&sockaddr,&len);
		if(clientFd < 0)
		{
			perror("acqurie--------- clientFd error");
			return ;
		}

		//记录客户端的socket
		fds[size++] = clientFd;
		printf("I am clientFd = [%d],I go one the line\n",clientFd);

		//有客户端接入后,启动线程给此客户端服务
		pthread_t tid;
		pthread_create(&tid,0,service_thread,&clientFd);
		
		
	 }
}

int main(int argc,char **args)
{
	int socketFd;

	if(argc > 2)
		IP_PORT = atoi(args[1]);
	if(argc > 3)
		strncpy(IP_ADDRESS,args[2],sizeof(&args));

	socketFd = initServer();
	pid_t pid = CreateNewProc(AcceptClient,socketFd);
}

