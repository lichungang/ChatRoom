/*************************************************************************
	> File Name: client.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月28日 星期日 00时35分47秒
 ************************************************************************/

#include"Connect.h"
int IP_PORT = 9000;
char *IP_ADDRESS = "127.0.0.1";
char name[20];
char buff[100] = {};
int clientFd;

int connectServer()
{
	struct sockaddr_in clientaddr;

	clientFd = socket(AF_INET,SOCK_STREAM,0);
	if(clientFd < 0)
	{
		perror("acquire socketFd error");
		return 0;
	}
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(IP_PORT);
	clientaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	printf("clientFd = [%d]\n",clientFd);

	int ret = connect(clientFd,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
	if(ret < 0)
	{
		perror("linking server error");
		return -1;
	}
	
}

void * recv_thread(void *p)//此线程用来接收消息
{
	
	while(1)
	{
		int ret;
		char buf[100] = {};
		
		ret = recv(clientFd,buf,sizeof(buf),0);
		if(ret<= 0)
		{
			perror("client recv msg error");
			return ;
		}

		printf("%s\n",buf);
	}
}

void RecvOtherClientFd()
{
	int ret;

	pthread_t tid;
	ret = pthread_create(&tid,0,recv_thread,NULL);//开辟此线程用来接收消息
	if(ret != 0)
	{
		perror("create pthread error\n");
		return ;
	}

	while(1)//发送消息
	{
		char msg[100];
		scanf("%s",buff);

		if(strcmp("BYE",buff) == 0)
		{
			sprintf(msg,"%s : wo xia le byebye",name);
			send(clientFd,msg,strlen(msg),0);
			system("clear");
			return ;
		}

		sprintf(msg,"%s saying : %s",name,buff);
		ret = send(clientFd,msg,strlen(msg),0);
		if(ret == -1)
		{
			perror("send msg error");
			return ;
		}

		memset(buff,0,sizeof(buff));
	    memset(msg,0,sizeof(msg));
	}
}
int main(int argc,char **args)
{
	int ret;

	if(argc > 2)
		IP_PORT = atoi(args[1]);
	if(argc > 3)
		strncpy(IP_ADDRESS,args[2],sizeof(&args[2]));

	connectServer();
	printf("please input your name:");
	scanf("%s",name);
	printf("name = [%s]\n",name);
	system("clear");
	puts("-=-=-=-=-=-=-=-=-=-=-=-=CHAT ROOM-=-=-=-=-=-=-=-=-=-=-=-=-=");
	puts("begin chat:\n");

	RecvOtherClientFd();
}
