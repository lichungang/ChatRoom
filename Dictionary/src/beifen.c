/*************************************************************************
	> File Name: function.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月08日 星期一 16时54分17秒
 ************************************************************************/

#include"Dictionary.h"

int DelectWordFromBook(FILE * Fp)
{
	char buf[80];//输入需要查找的单词
	char str[256];//查找出来的单词
	int leng;
	int i;
	int ret;

	puts("您要从单词本中删除哪个单词吗?1/0");
Next_To:
	scanf("%d",&i);
	if(1 == i)	
	{
		puts("请输入您要从单词本中删除的单词");

		scanf("%s",buf);

		while(1)
		{
			ret = FindWordFrom(Fp,str,buf);//找到了要删除的单词
			if(ret == 0)
			{
				printf("您要删除的单词是 %s \n",str);
				rewind(Fp);
				break;
			}
		}
	}
	else if(0 == i)
		;
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
int FindWordFrom(FILE *Fd,char *str,char *buff)
{
	int len;
	int ret;

	len = strlen(buff);	//要查的这个单词有len个字母
	fgets(str,512,Fd);	//从文件中读取一行，读取后文件指针自动移向下一行
	if(str == NULL)
	{
		perror("读取文件失败");
		return 0;
	}
	ret = strncmp(str,buff,len);	//将读到的str字符串的前len个字符和输入的单词比较
		
	return ret;
}
int ReferWord(FILE* Fd)
{
	system("clear");

	char buff[128];
	char str[512];
	char buf[512];
	int leng;
	int i;
	int ret;

	printf("请输入您所要查询的单词: ");
	scanf("%s",buff);
		
	while(1)
	{
	
		ret = FindWordFrom(Fd,str,buff); //
		leng = strlen(str);	//读取的字符串的长度
	
		if(0 == ret)
		{
			for(i = 0; i < leng; i++)
			{
				if(*(str+i) == '#' )
					printf("\n");
				else
					printf("%c",*(str+i));
			}

			AddWordTo(str);	//加入单词本
			printf("\n");

			rewind(Fd);		//将文件指针重新定位至文件的开始
			break;
		}

		ret = feof(Fd);		//检查文件流是否到了末尾，如果到了末尾则返回非零（！0），否则返回零（0）
		if(ret != 0)
		{
			puts("查无此单词");
			rewind(Fd);
			break;
		}
	}

	puts("请输入您所要使用的功能");
	return 1;
}

int InsertWord(FILE *Fd)
{
	
}

int DelectWord()
{
	
}

int WordsBook()
{
	FILE * Fp;
	char buf[256];
	int leng;
	int i;
	Fp = fopen("./../log/ReviewWordsBook.txt","a+");
	if(Fp == NULL)
	{	
		perror("在WorksBook中打开文件失败");
		return -1;
	}

	while(fgets(buf,sizeof(buf),Fp) != NULL)
	{	
		leng = strlen(buf);
	//	puts(buf);
		for(i = 0; i < leng; i++)
		{
			if(*(buf+i) == '#' )
				printf("\n");
			else
				printf("%c",*(buf+i));

		//	printf("\n");
		}
			printf("\n");
	}
	rewind(Fp);
	DelectWordFromBook(Fp);

	puts("请输入您所要使用的功能");
	return 0;
}

int Exit(FILE * Fd)
{
	system("clear");
	puts("感谢您的使用，期待您下次继续使用");
	fclose(Fd);
	exit(0);
}
