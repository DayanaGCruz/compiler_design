%option noyywrap yylineno nodefault outfile="lexer.c"
%{ 
	#include "parser.tab.h"
	#include "ast.h"
	#include "symboltable.h"
	extern int syntaxerrorno;
	int lexerrorno;	
	int lnolastid; // Holds line no of the last identifier token found
	int* sen = &syntaxerrorno;
	int* len = &lexerrorno;
/*	void yyerror (char* s, int errType) {
		if(errType == 1){(*sen)++; printf("Incremented syntax error");} 
		else if (errType == 0) {(*len)++;} 
		fprintf(stderr, "Ln.%d: %s: %s\n", yylineno, s, yytext);
	}*/
	void yyerror (char* s) {
}	
%}

IDENTIFIER  [A-Za-z_]+[A-Za-z0-9_]*
COMMENT		"//".*
INT		    [0-9]+[0.-9]*
FLOAT		[0-9]+.[0-9]+
KW_IF		"if"
KW_ELSE		"else"
KW_INT		"int"
KW_FLOAT		"float"
KW_PRINT		"write"
KW_RETURN	"return"
KW_WHILE		"while"
KW_FOR		"for"
ASSIGN		"="
AND			"&&"
OR			"||"
LTHAN		"<"
GTHAN		">"
LTHANEQ		"<="
GTHANEQ		">="
EQ			"=="
NOTEQ		"!="
NOT			"!"
PLUS		"+"
MINUS		"-"
MUL			"*"
DIV			"/"
LPAREN		"("	
RPAREN		")"
LCURLY		"{"
RCURLY		"}"
LBRACKET	"["
RBRACKET	"]"
SEMICOLON	";"
COMA		","
%%
[ \t\n]*	{/*Ignore whitespace*/}
{COMMENT} {
	// Ignore comments
	printf("Ln.%d : LEXER : // COMMENT: %s\n", yylineno, yytext);
	}
{KW_PRINT}	{
		printf("Ln.%d : LEXER : PRINT KEYWORD: %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_PRINT;
		}	
{KW_RETURN}	{
		printf("Ln.%d : LEXER :  KEYWORD: %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_RETURN;
}
{KW_FLOAT}	{
		printf("Ln.%d: LEXER : FLOAT TYPE KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_FLOAT;
			}
{KW_INT}		{
		printf("Ln.%d: LEXER: INTEGER TYPE KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_INT;
			}
{KW_IF}		{
		printf("Ln.%d: LEXER: IF KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_IF;
			}
{KW_ELSE}	{
		printf("Ln.%d: LEXER: ELSE KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_ELSE;
	}
{KW_WHILE}	{
		printf("Ln.%d: LEXER: WHILE KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_WHILE;
		}
{KW_FOR}		{
		printf("Ln.%d: LEXER: FOR KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return KW_FOR;
			}	
{IDENTIFIER}	{
		lnolastid = yylineno;
		printf("Ln.%d: LEXER : IDENTIFIER : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return IDENTIFIER;
		}
{FLOAT}		{
		printf("Ln.%d: LEXER : FLOAT: %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return FLOAT;
		}
{INT}		{
		printf("Ln.%d : LEXER : INT: %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return INT;
		}
{PLUS}		{
		printf("Ln.%d : LEXER : PLUS OP: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return PLUS;
		}
{MINUS}		{
		printf("Ln.%d : LEXER : MINUS OP: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return MINUS;
		}
{MUL}		{
		printf("Ln.%d : LEXER : MUL OP: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return MUL;
		}
{DIV}		{
		printf("Ln.%d : LEXER : DIV OP: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return DIV;
		}
{AND}	{
		printf("Ln.%d: LEXER: LOGICAL AND : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return AND;
		}
{OR}	{
		printf("Ln.%d: LEXER: LOGICAL OR : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return OR;
		}
{LTHAN}	{
		printf("Ln.%d: LEXER: LOGICAL LESS THAN : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return LTHAN;
		}
{GTHAN}	{
		printf("Ln.%d: LEXER: LOGICAL GREATER THAN : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return GTHAN;
		}
{LTHANEQ} {
		printf("Ln.%d: LEXER: LOGICAL LESS THAN OR EQUAL : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return LTHANEQ;
		}
{GTHANEQ} {
		printf("Ln.%d: LEXER: LOGICAL GREATER THAN OR EQUAL : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return GTHANEQ;
		}
{EQ}	{
		printf("Ln.%d: LEXER: LOGICAL EQUAL TO : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return EQ;
		}
{NOTEQ} {
		printf("Ln.%d: LEXER: LOGICAL NOT EQUAL TO : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return NOTEQ;
		}
{NOT}	{
		printf("Ln.%d: LEXER: LOGICAL NOT : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return NOT;
		}
{LPAREN}	{
		printf("Ln.%d : LEXER : OPEN PARENTHESIS: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return LPAREN;
		}
{RPAREN}	{
		printf("Ln.%d : LEXER : CLOSING PARENTHESIS: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return RPAREN;
		}
{LCURLY}	{
		printf("Ln.%d : LEXER : OPEN CURLY BRACE: %s\n", yylineno, yytext);
		return LCURLY;
		}
{RCURLY}		{
		printf("Ln.%d : LEXER : CLOSING CURLY BRACE: %s\n", yylineno, yytext);
		return RCURLY;
		}
{ASSIGN}	{
		printf("Ln.%d : LEXER : ASSIGN OP: %s\n", yylineno, yytext);
		yylval.operator = strdup(yytext);
		return ASSIGN;
		}
{SEMICOLON}	{
		printf("Ln.%d : LEXER : SEMICOLON: %s\n", yylineno, yytext);
		return SEMICOLON;
		}
{COMA}  	{
		printf("Ln.%d : LEXER : COMA: %s\n", yylineno, yytext);
		return COMA;
}
{LBRACKET}	{
		printf("Ln.%d : LEXER : OPEN BRACKET: %s\n", yylineno, yytext);
		return LBRACKET;
}
{RBRACKET}	{
		printf("Ln.%d : LEXER : CLOSING BRACKET: %s\n", yylineno, yytext);
		return RBRACKET;
}
[A-Za-z0-9\_\-\.]* { //Digits, hyphens, and letters NOT INT FLOAT KEYWORD or IDENTIFIER generate generic lexical error messages
	
 // yyerror("LEXER : Lexical Error: Illegal Identifier", 0);
		}
. 		{ // Symbols not included in grammar generate lexical error messages - illegal symbol
	//	yyerror("LEXER : Lexical Error: Illegal symbol", 0);
		}
%%

