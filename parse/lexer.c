

#include "str.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>


FILE *using_fp = NULL;
int line = 0;//行数
int cols = 0;//列数


BOOL IsIdentifier(const char *str)
{
    if (!IsDigit(str[0]))
    {
        unsigned int i;
        for (i = 1; i < strlen(str); i++)
        {
            if (!IsLetter(str[i]) && !IsDigit(str[i]) && str[i] != '_')
                return FALSE;
        }
        return TRUE;
    }
    else
        return FALSE;
}


BOOL IsLetter(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return TRUE;
    return FALSE;
}


BOOL IsDigit(int ch)
{
    if (ch >= '0' && ch <= '9')
        return TRUE;
    return FALSE;
}


BOOL IsSymbol(int ch)
{
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case '!':
    case '<':
    case '>':
    case '.':
    case '&':
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case ';':
    case ',':
    //case '\'':
    //case '\"':
        return TRUE;
    }

    return FALSE;
}


TokenCode IsKeyWord(const char* str)
{
    if (strcmp(str,"void") == 0)
        return KW_VOID;
    else if (strcmp(str, "short") == 0)
        return KW_SHORT;
    else if (strcmp(str, "int") == 0)
        return KW_INT;
    else if (strcmp(str, "long") == 0)
        return KW_LONG;
    else if (strcmp(str, "float") == 0)
        return KW_FLOAT;
    else if (strcmp(str, "double") == 0)
        return KW_DOUBLE;
    else if (strcmp(str, "char") == 0)
        return KW_CHAR;
    else if (strcmp(str, "string") == 0)
        return KW_STRING;
    else
        return TK_IDENT;
}


BOOL NextIsAppointChar(FILE* fp, int ch, BOOL if_is_fp_back)
{
    if (ch == fgetc(fp))
    {
        if(if_is_fp_back)
            fseek(fp, -1L, SEEK_CUR);
        return TRUE;
    }
    fseek(fp, -1L, SEEK_CUR);
    return FALSE;
}


BOOL NextIsAppointString(FILE* fp, const char* str, BOOL if_is_fp_back)
{
    int i;
    int length = strlen(str);
    for (i = 0; i < length; i++)
    {
        if (!NextIsAppointChar(fp, str[i], if_is_fp_back))
        {
            fseek(fp, -(i * 1L), SEEK_CUR);
            return FALSE;
        }
    }
    if (if_is_fp_back)
        fseek(fp,-length,SEEK_CUR);
    return TRUE;
}


/*
BOOL NextIsChineseCharacter(FILE *fp)
{
    if (fgetc(fp) < 0)
    {
        fseek(fp, -1L, SEEK_CUR);
        return TRUE;
    }
    fseek(fp, -1L, SEEK_CUR);
    return FALSE;
}
*/


Token *GetNextToken(FILE *fp)
{
    TokenCode type = 0;
    char *value = (char*)calloc(1,sizeof(char));


    if(using_fp != fp)
    {
        using_fp = fp;
        line = 0;
        cols = 0;
        fseek(fp,0L,SEEK_SET);
    }


    int ch;


    while (1)
    {
        ch = fgetc(fp);
        cols++;
        
        switch (ch)
        {
        case EOF:
            return NULL;

        case ' ':
        case '\t':
        case '\r':
            continue;
        
        case '\n':
            line++;
            cols = 0;
            continue;

        /*
        case ';':
            return TokenCreate(TK_SEMICOLON,";",line,cols);
        */
        
        default:
            break;
        }

        break;
    }
    
    
    if (ch == '\'' || ch == '\"')
    {
        char prev = ch;
        while (1)
        {
            ch = fgetc(fp);
            cols++;
            if (ch == prev)
                break;
            
            switch (ch)
            {
            case EOF:
                return NULL;
            
            default:
                StrAddChar(value,ch);
                break;
            }
        }
        
        return TokenCreate(TK_CSTR,value,line,cols);
    }
    

    if (IsSymbol(ch))
    {
        //sprintf(value,"%c",ch);
        StrAddChar(value,ch);
        return TokenCreate(ch,value,line,cols);
    }
    

    if (IsLetter(ch) || ch == '_')
    {
        StrAddChar(value,ch);
        while (1)
        {
            ch = fgetc(fp);
            cols++;

            if (IsLetter(ch) || ch == '_')
            {
                StrAddChar(value,ch);
            }
            else
            {
                cols--;
                fseek(fp,-1L,SEEK_CUR);
                break;
            }
        }

        type = IsKeyWord(value);
        return TokenCreate(type,value,line,cols - strlen(value));
    }


    if (IsDigit(ch))
    {
        StrAddChar(value,ch);
        while (1)
        {
            ch = fgetc(fp);
            cols++;

            if (IsDigit(ch) || ch == '.')
                StrAddChar(value,ch);
            else
            {
                cols--;
                fseek(fp,-1L,SEEK_CUR);
                break;
            }
        }
        
        return TokenCreate(TK_CNUMBER,value,line,cols - strlen(value));
    }
    


    return NULL;
}

