
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/lexer.h"


int main(int argc,char *argv[])
{
	if (argc > 1)
	{
		//printf("%s\n",argv[1]);
		FILE *log = fopen("./log.txt","w");
		FILE *fp = fopen(argv[1],"r");
		//Token *token = NULL;
		if (fp != NULL)
		{
			printf("Lex\n");


			/*
			while ((token = GetToken(fp)) != NULL)
			{
				TokenPrint(token);
				TokenWrite(token,log);
				free(token);
				token = NULL;
			}
			*/
			

			TokenStream *stream = Lex(fp);
			TokenStreamTokensPrint(stream);
			TokenStreamTokensWrite(stream,log);
		}
	}
	else if (argc == 1)
		printf("Please specify an input file.\n");
	return 0;
}



