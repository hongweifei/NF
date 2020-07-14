

#include "../str.h"
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
	if (token != NULL)
	{
		printf("Type: %d\n",token->type);

		if (token->value != NULL)
			printf("Value: %s\n",token->value);
			
		printf("line: %d\n",token->line);
		printf("cols: %d\n\n",token->cols);
	}
}


void TokenWrite(Token *token,FILE *fp)
{
	if (token != NULL && fp != NULL)
	{
		fputs("Type:",fp);
		fputs(IToA(token->type),fp);
		fputc('\n',fp);

		if (token->value != NULL)
		{
			fputs("Value:",fp);
			fputs(token->value,fp);
			fputc('\n',fp);
		}

		fputs("Line:",fp);
		fputs(IToA(token->line),fp);
		fputc('\n',fp);

		fputs("Cols:",fp);
		fputs(IToA(token->cols),fp);
		fputs("\n\n",fp);
	}
}




TokenStream *TokenStreamInit()
{
	TokenStream *stream = (TokenStream*)malloc(sizeof(TokenStream));
	
	stream->token = (Token**)calloc(1,sizeof(Token*));
	stream->token[0] = NULL;
	stream->count = 0;

	return stream;
}


void TokenStreamAppend(TokenStream *stream,Token *token)
{
	if (token != NULL)
	{
		stream->count++;
		stream->token = (Token**)realloc(stream->token,sizeof(Token*) * stream->count);
		stream->token[stream->count - 1] = token;
	}
}



Token *TokenStreamGetItem(TokenStream *stream,unsigned int index)
{
	return stream->token[index];
}


Token **TokenStreamGetAllToken(TokenStream *stream)
{
	return stream->token;
}



void TokenStreamTokenPrint(TokenStream *stream,unsigned int index)
{
	Token *token = stream->token[index];
	TokenPrint(token);
}


void TokenStreamTokenWrite(TokenStream *stream,unsigned int index,FILE *fp)
{
	Token *token = stream->token[index];
	TokenWrite(token,fp);
}


void TokenStreamTokensPrint(TokenStream *stream)
{
	for (unsigned int i = 0; i < stream->count; i++)
		TokenPrint(stream->token[i]);
}


void TokenStreamTokensWrite(TokenStream *stream,FILE *fp)
{
	for (unsigned int i = 0; i < stream->count; i++)
		TokenWrite(stream->token[i],fp);
}






