

#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




Token *TokenCreate(TokenCode type,char *value,int line,int cols)
{
	Token *token = (Token*)malloc(sizeof(Token));

	token->type = type;
	token->value = value;
	token->line = line;
	token->cols = cols;
	
	//short length = strlen(value);
	//TokenSetText(token,value);

	return token;
}



void TokenSetTypeAndText(Token* token, TokenCode type, const char* text)
{
	//TokenSetType(token, type);
	//TokenSetText(token, text);

	token->type = type;

	unsigned int length = strlen(text);
	token->value = (char*)malloc(sizeof(char) * length);

	strcpy(token->value,text);
}


void TokenSetTypeAndChar(Token* token, TokenCode type, int ch)
{
	//TokenSetType(token, type);
	//TokenSetChar(token, ch);

	token->type = type;

	token->value = (char*)calloc(1,sizeof(char));
	sprintf(token->value,"%c",ch);
}


void TokenSetType(Token* token, TokenCode type)
{
	token->type = type;
}


void TokenSetText(Token *token,const char *text)
{
	unsigned int length = strlen(text);
	token->value = (char*)malloc(sizeof(char) * length);

	strcpy(token->value,text);
}


void TokenSetChar(Token* token, int ch)
{
	token->value = (char*)calloc(1,sizeof(char));
	sprintf(token->value,"%c",ch);
}


void TokenAddChar(Token* token, int ch)
{
	unsigned int length = strlen(token->value);//不算\0
	token->value = (char*)realloc(token->value,sizeof(char) * (length + 1 + 1));

	token->value[length] = (char)ch;
	token->value[length + 1] = '\0';

	//char str[2] = {'\0'};
	//sprintf(str, "%c", ch);
	//strcat(token->value,str);
}



void TokenPrint(Token *token)
{
	printf("Type: %d\n",token->type);
	printf("Value: %s\n",token->value);
	printf("line: %d\n",token->line);
	printf("cols: %d\n\n",token->cols);
}


