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
	void yyerror (char* s, int errType) {
		if(errType == 1){(*sen)++; printf("Incremented syntax error");} 
		else if (errType == 0) {(*len)++;} 
		fprintf(stderr, "Ln.%d: %s: %s\n", yylineno, s, yytext);
	}

	/*
	struct 
	{
		bool success = false;
		struct 
		{
			int lineno;
			char* errMessage;
		} errLogLine;
		int lineno[];
		void printCompilationResults
		{
			printf(%s ERROR %s %-10s lineno : %-10s");
		}
	} compilationErrorLog;
	*/
%}

IDENTIFIER  [A-Za-z_]+[A-Za-z0-9_]*
COMMENT		"//".*
INT		    [0-9]+[0.-9]*
FLOAT		[0-9]+.[0-9]+
INTKW		"int"
FLOATKW		"float"
PRINTKW		"write"
RETURNKW	"return"
ASSIGN		"="
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
<<EOF>> {return 0;}
[ \t\n]*	{/*Ignore whitespace*/}
{COMMENT} {
	// Ignore comments
	printf("Ln.%d : LEXER : // COMMENT: %s\n", yylineno, yytext);
	}
{PRINTKW}	{
		printf("Ln.%d : LEXER : PRINT KEYWORD: %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return PRINTKW;
		}	
{RETURNKW}	{
		printf("Ln.%d : LEXER : RETURN KEYWORD: %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return RETURNKW;
}
{FLOATKW}	{
		printf("Ln.%d: LEXER : FLOAT TYPE KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return FLOATKW;
			}
{INTKW}		{
		printf("Ln.%d: LEXER: INTEGER TYPE KEYWORD : %s\n", yylineno, yytext);
		yylval.string = strdup(yytext);
		return INTKW;
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
		yyerror("LEXER : Lexical Error: Illegal Identifier", 0);
		}
. 		{ // Symbols not included in grammar generate lexical error messages - illegal symbol
		yyerror("LEXER : Lexical Error: Illegal symbol", 0);
		}
%%

