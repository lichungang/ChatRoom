/*************************************************************************
	> File Name: function.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月08日 星期一 16时54分17秒
 ************************************************************************/

#include"Dictionary.h"

/*FILE *MoveFileTo(FILE *Fp,char *str,int f)
{
	FILE * Fd,Fe;
	char buf[512];
	int ret;
	int i;
	int j;
	int k = 0;

	Fd = fopen("./../log/DelectExchanheFile.txt","w+");
	if(Fd == NULL)
	{
		perror("代开交换文件失败");
		return NULL;
	}

	Fe = fopen("./../log/tmp.txt","w+r+");
	
	if(Fe == NULL)
	{
		perror("代开交换文件失败");
		return NULL;
	}

	for(i = 1; i < f; i++)	//读到要删除的前一行
	{
		 fgets(buf,sizeof(buf),Fp);

		 fputs(buf,Fd);
		 k++;
	}

	printf("k = [%d]\n",k);
    fgets(buf,sizeof(buf),Fp);
	printf("---k-- = [%d]\n",k);
//	memset(buf,0,sizeof(buf));

	for(i = 0; ;i++)
	{
		
		fgets(buf,sizeof(buf),Fp);
		j = feof(Fp);		//检查文件流是否到了末尾，如果到了末尾则返回非零（！0），否则返回零（0）
		if(j != 0)
		{
			rewind(Fp);
			break;
		}

		fputs(buf,Fd);
		printf("---k-- = [%d]\n",k);
		k++;
	}
	printf("k = [%d]\n",k);

	rewind(Fd);	//让Fd指向文件的开始
	rewind(Fp);

	for(i = 1; i <= k; i++)
	{
		fgets(buf,sizeof(buf),Fd);

		fputs(buf,Fe);
		printf("[--%d--]\n",k);
	}
	printf("--%d--\n",k);
	rewind(Fp);
	rewind(Fd);
	rewind(Fe);

	fclose(Fd);

	system("rm -Rf ReviewWordsBook.txt");
	system

	while(1)
	{
		fgets(buf,sizeof(buf),Fp);
		j = feof(Fp);		//检查文件流是否到了末尾，如果到了末尾则返回非零（！0），否则返回零（0）
		if(j != 0)
		{
			rewind(Fp);
			break;
		}
		puts(buf);
	}
	return Fp;
}
*/

int DelectWordFromBook()
{

	FILE * Fp;
	char buf[80];//输入需要查找的单词
	char str[256];//查找出来的单词
	int leng;
	int i ;
	int f;
	char *ret ;

	Fp = fopen("./../log/ReviewWordsBook.txt","a+");
	puts("您删除哪个单词吗?1/0");

Next_To:
	scanf("%d",&i);

	if(1 == i)	
	{
		puts("请输入您要从单词本中删除的单词");
		scanf("%s",buf);
		
		f = 0;
		ret = FindWordFrom(Fp,str,buf,&f,20);//找到了要删除的单词
		if(ret == NULL)
		{
			printf("在 %d 行找到这龟儿子了\n",f);
			printf("=====您要删除的单词是 %s \n",str);
			rewind(Fp);

		//	MoveFileTo(Fp,str,f);
		}

	}
	else if(0 == i)
	{}
	else 
	{
		puts("输入错误，1 代表 是，0 代表否，请您重新输入");
		goto Next_To;
	}

}

void AddWordTo(char *str)
{
	FILE * Fp;
	int c;

First_To:
	puts("是否加入单词本？1/0");
	scanf("%d",&c);

	if(1 == c)
	{
		Fp = fopen("./../log/ReviewWordsBook.txt","a+");
		if(Fp == NULL)
		{
			perror("打开ReviewWordsBook失败");
			return;
		}

		fputs(str,Fp);
		printf("加入单词本成功\n");
		fclose(Fp);
	}
	else if(0 == c)
		;
	else
	{
		puts("您的输入有误，1 代表是， 0 代表否，请重新输入");
		goto First_To;
	}
}
char * FindWordFrom(FILE *Fd,char *str,char *buff,int *row,int WordsLines)
{
	char *words[WordsLines];
	int len;
	int d;
	int i = 0;
	int ret;

	len = strlen(buff);	//要查的这个单词有len个字母
	printf("len = [%d]\n",len);

	for(i = 0; i < WordsLines; i++)		//读到内存.即字符数组
	{
		words[i] = (char *)malloc(256);
		fgets(words[i],256,Fd);
		if(words[i] == NULL)
		{
			perror("读取文件失败");
			return NULL;
		}
//	}
//	for(i = 0; i < WordsLines;i++)
//	{
		ret = strncmp(words[i],buff,len);	//将读到的str字符串的前len个字符和输入的单词比较
		if(ret == 0)
		{
			*row = i;
			rewind(Fd);
			break;
		}

		if(i == WordsLines - 1)
		{
			rewind(Fd);
			printf("查无此单词\n");
			return NULL;
		}
	}

	
	
/*		int head = 0;
		int tail = WordsLines;
	
		 i = 0;
		long mode = (head + tail)/2;
		while(1)
		{
			i++;	

			ret = strncmp(words[mode],buff,len);	//将读到的str字符串的前len个字符和输入的单词比较
			if(ret > 0)
			{
				tail = mode - 1;
			}
			else if(ret < 0)
			{
				head = mode + 1;
			}
			else
			{
				printf("总共找了 %d ci\n",i);
				break;
			}
			 mode = (head + tail)/2;

			 if(i > 20)
			 {
				printf("无此单词\n");
				break;
			 }
		}
*/	
	str = (char *)malloc(256);
	strncpy(str,words[i],256);


	//	fgets(str,256,words[i]);
//	printf("%s",str);
/*	while(0 != ret)
	{
		fgets(str,512,Fd);	//从文件中读取一行，读取后文件指针自动移向下一行
		if(str == NULL)
		{
			perror("读取文件失败");
			break;
			return 0;
		}
		
		(*row)++;
		ret = strncmp(str,buff,len);	//将读到的str字符串的前len个字符和输入的单词比较
		if(ret == 0)
		{
			printf("找到了\n");
			rewind(Fd);
			break;
		}
		
		d = feof(Fd);		//检查文件流是否到了末尾，如果到了末尾则返回非零（！0），否则返回零（0）
		if(d != 0)
		{
			puts("查无此单词");
			rewind(Fd);
			break;
		}
	}	*/
	return str;
}

	

