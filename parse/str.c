

#include "str.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void StrSetStr(char *str, const char *text)
{
    unsigned int length = strlen(text);
	str = (char*)calloc(length + 1,sizeof(char));

	strcpy(str,text);
}



void StrSetChar(char *str, int ch)
{
    str = (char*)calloc(1,sizeof(char));
	sprintf(str,"%c",ch);
}



void StrAddChar(char *str, int ch)
{
    unsigned int length = strlen(str);//不算\0
	str = (char*)realloc(str,sizeof(char) * (length + 2));
	
	str[length] = (char)ch;
	str[length + 1] = '\0';

}


int NumDigits(int n)
{
    int digits = 0;
    if (n <= 0)
	{
        n = -n;
        ++digits;
    }
    while (n)
	{
        n /= 10;
        ++digits;
    }
    return digits;
}



char *ItoA(int number)
{
    char *dest = (char*)malloc(sizeof(char) * (NumDigits(number) + 1));
	sprintf(dest,"%d",number);
	return dest;
}








