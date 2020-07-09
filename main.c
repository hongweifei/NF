
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/lexer.h"
#include "parse/str.h"


int main(int argc,char *argv[])
{
	if (argc > 1)
	{
		//printf("%s\n",argv[1]);
		FILE *log = fopen("./log.txt","w");
		FILE *fp = fopen(argv[1],"r");
		if (fp != NULL)
		{
			Token *token = NULL;
			while ((token = GetNextToken(fp)) != NULL)
			{
				//printf("%s  %d\n", token->value, token->type);
				TokenPrint(token);

				fputs("Type:",log);
				fputs(ItoA(token->type),log);
				fputc('\n',log);

				fputs("Value:",log);
				fputs(token->value,log);
				fputc('\n',log);

				fputs("Line:",log);
				fputs(ItoA(token->line),log);
				fputc('\n',log);

				fputs("Cols:",log);
				fputs(ItoA(token->cols),log);
				fputs("\n\n",log);

				free(token);
			}
		}
	}
	else if (argc == 1)
		printf("Please specify an input file.\n");
	return 0;
}

