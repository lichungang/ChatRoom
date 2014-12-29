/*************************************************************************
	> File Name: dictionary.c
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月08日 星期一 15时58分35秒
 ************************************************************************/
/*
 *英汉小词典
 * */

#include"Dictionary.h"

void InitDic()
{
	puts("-------------------------英汉小词典----------------------------\n");
	puts("1 查询单词 \n");
	puts("2 添加单词 \n");
	puts("3 删除单词 \n");
	puts("4 单词本\n");
	puts("5 退出使用\n");
	puts("---------------------------------------------------------------\n");
}

void SelectFunc(FILE *Fd)
{
	int a;
	puts("请输入您所要使用的功能");

	while(1)
	{
		scanf("%d",&a);
		switch(a)
		{
			case 1: ReferWord(Fd);  //查单词
					break;
			case 2: InsertWord(Fd);	//向词库中加入单词
				    break;
			case 3: DelectWord();	//从词库中删除一个单词
					break;
			case 4: WordsBook();	//从单词本中查看单词
					break;
			case 5: Exit(Fd);		//退出程序

			default:puts("输入错误，请重输");
		}
	}

}
int main(void)
{
	FILE *Fd;
	int ret;
	InitDic();
	
	Fd = fopen("./../log/DictionaryFile.txt","r+w+");
	if(Fd == NULL)
	{
		perror("打开文件失败");
		return -1;
	}

	SelectFunc(Fd);
	
	ret = fclose(Fd);

	return 0;
}

