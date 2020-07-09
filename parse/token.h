
#pragma once




typedef enum
{
    /*运算符和分隔符*/
    TK_PLUS = '+',                  // +   加号
    TK_MINUS = '-',                 // -   减号
    TK_STAR = '*',                  // *   乘号
    TK_DIVIDE = '/',                // /   除号
    TK_MOD = '%',                   // %   求余运算符
    TK_EQ = 15677,                  // ==  等号
    TK_NEQ = 8509,                  // !=  不等号
    TK_LT = '<',                    // <   小于号
    TK_LEQ = 15421,                 // <=  小于等于号
    TK_GT = '>',                    // >   大于号
    TK_GEQ = 15933,                 // >=  大于等于号
    TK_ASSIGN = '=',                // =   赋值运算符
    TK_POINTSTO = 11582,            // -> 
    TK_DOT = '.',                   // .  
    TK_AND = '&',                   // &   地址与运算符
    TK_OR = '|',                    // |

    TK_OPENPA = '(',                // (   左圆括号
    TK_CLOSEPA = ')',               // )   有圆括号
    TK_OPENBR = '[',                // [   左中括号
    TK_CLOSEBR = ']',               // ]   右中括号
    TK_BEGIN = '{',                 // {   左大括号
    TK_END = '}',                   // }   右大括号
    TK_SEMICOLON = ';',             // ;   分号
    TK_COMMA = ',',                 // ,   逗号
    TK_ELLIPSIS = 3026478,          // ... 省略号

    TK_EOF = 0,             //文件结束符

    /*标识符*/
    TK_IDENT,       //标识符

    /**/
    TK_CNUMBER,     //
    TK_CCHAR,       //
    TK_CSTR,        //

    /*关键字*/
    KW_VOID,        // void关键字
    KW_SHORT,       // short关键字
    KW_INT,         // int关键字
    KW_LONG,        // long关键字
    KW_FLOAT,       // float
    KW_DOUBLE,      // double
    KW_CHAR,        // char关键字
    KW_STRING       // string
}TokenCode;


typedef struct
{
    TokenCode type;
	char *value;
    int line;
    int cols;
}Token;



Token *TokenCreate(TokenCode type,char *value,int line,int cols);


void TokenSetTypeAndText(Token *token, TokenCode type,const char *text);
void TokenSetTypeAndChar(Token *token, TokenCode type, int ch);

void TokenSetType(Token *token,TokenCode type);
void TokenSetText(Token *token, const char *text);
void TokenSetChar(Token *token, int ch);

void TokenAddChar(Token *token,int ch);


void TokenPrint(Token *token);