/*************************************************************************
	> File Name: function.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月08日 星期一 16时54分17秒
 ************************************************************************/

#include"Dictionary.h"


int ReferWord(FILE* Fd)
{
	system("clear");

	char InputWord[128];
	char str[512];
	char buf[512];
	int leng;
	int i;
	int WordsLines = 44013;
	int row = 0;
	char *ret;
	clock_t begin,end;
	double cost;

	begin = clock();
	printf("请输入您所要查询的单词: ");
	scanf("%s",InputWord);
	
	printf("wordleng = [%ld]\n",sizeof(InputWord));
	ret = FindWordFrom(Fd,str,InputWord,&row,WordsLines); //
	leng = strlen(ret);	//读取的字符串的长度
	
	if(NULL != ret)
	{
		end = clock();
		cost = (double)(end - begin);
		printf("查询单词用时 cost = [%lf]\n",cost/CLOCKS_PER_SEC);

		printf("在第 %d 行找到了\n",row);
		for(i = 0; i < leng; i++)
		{
			if(*(ret+i) == '#' )
				printf("\n");
			else
				printf("%c",*(ret+i));
		}

		AddWordTo(ret);	//加入单词本
		printf("\n");
		rewind(Fd);		//将文件指针重新定位至文件开头
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
	fclose(Fp);
	
	DelectWordFromBook();

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
