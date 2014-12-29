/*************************************************************************
	> File Name: dictionary.h
	> Author: lichungang
	> Mail: 710901221@qq.com
	> Created Time: 2014年12月08日 星期一 15时59分13秒
 ************************************************************************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<time.h>

#define TRUE   1
#define FALSE  0


char *FindWordFrom(FILE *Fd,char *str,char *buff,int * row,int WordsLines);
void AddWordTo(char *str);
int DelectWordFromBook();
int ReferWord(FILE * Fd);
int InsertWord();
int DelectWord();
int WordsBook();
int Exit(FILE *Fd);
void SelectFunc();
#endif
