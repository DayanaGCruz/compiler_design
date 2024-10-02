%define parse.error verbose

%{
#include "ast.h" /*Parse/AST Tree Management*/
#include "symboltable.h" /*Symbol Table Management*/
#include "semantic.h"
#include "factorlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int yylineno; /* Declared in lexer */
extern char* yytext;
extern int lexerrorno;
int semerrorno = 0; 
int syntaxerrorno = 0;
extern int yylex();
extern int yyparse();
extern void yyerror(); 
extern FILE* yyin;
extern int lnolastid; /*Symbol table util.*/
struct Node* root = NULL; /*AST Root Node*/
struct SymbolTable* symbolTable = NULL;

struct FactorNode* head = NULL;

%}

%union 
{
	struct Node* ast; /* Each rule will return an AST node */
    struct SymbolTable* st;
	struct Symbol* symbol;
	char* string; 
	char* operator;
}
%token PLUS MINUS MUL DIV
%token LPAREN RPAREN LCURLY RCURLY SEMICOLON
%token IDENTIFIER ASSIGN 
%token INT FLOAT 
%token PRINTKW INTKW FLOATKW 


%type <ast> program stmt_list stmt declaration assignment print_stmt type term factor number expr
%type <string> IDENTIFIER INTKW FLOATKW FLOAT INT// Specify that IDENTIFIER is of type identifier
%type <operator> ASSIGN MINUS PLUS MUL DIV

%%

program: stmt_list 
{
	$$ = createNode(node_program); /* Begin forming Parse tree/AST*/
	$$->program.stmt_list = $1;
	root = $$;
	printf("PARSER : Program successfully parsed\n");
}
	; 

stmt_list: stmt stmt_list 
{
	$$ = createNode(node_stmt_list);
	$$->stmt_list.stmt = $1;
	$$->stmt_list.stmt_list = $2;	
	printf("PARSER : Processed statement list\n");
}
	| 
	{
		/*empty*/ $$ = createNode(node_stmt_list); 
	}
	;
stmt: declaration 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
	}
	| assignment  
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
	}
	| print_stmt 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
	}
	| expr SEMICOLON 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
	}
	| expr error {syntaxerrorno++; printf("Ln.%d : SYNTAX ERROR : MISSING SEMICOLON\n", lnolastid);}

	;
declaration: type IDENTIFIER SEMICOLON 
	{
		printf("PARSER : PARSER : Found   declaration\n");
		$$ = createNode(node_declaration);
		$$->declaration.type = $1;
		$$->declaration.identifier = $2;
		if(lookupSymbol(symbolTable, $2) == NULL) 
		{
			insertSymbol(symbolTable, $2, $$->declaration.type->typekw.type, lnolastid);
		} else 
		{
			semerrorno++;
			printf("Ln.%d : SEMANTIC ERROR : Duplicate variable declaration\n", lnolastid);
		}
	}
	| type IDENTIFIER error {syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	;
type: FLOATKW
	{
		$$ = createNode(node_typekw);
		$$->typekw.type = $1;
	}
	| INTKW 
	{
		$$ = createNode(node_typekw);
		$$->typekw.type = $1;
	}
	;
assignment: IDENTIFIER ASSIGN expr SEMICOLON 
{
	$$ = createNode(node_assignment);
	$$->assignment.identifier = $1;
	$$->assignment.assign = $2;
	$$->assignment.expr = $3;
	/*SEMANTIC CHECK*/
	Symbol* symbol = lookupSymbol(symbolTable, $1);
	if(symbol == NULL)
	{
		semerrorno++;
		printf("Ln.%d : SEMANTIC ERROR: Undeclared variable usage : %s\n", yylineno, $1);
	}
}
	| IDENTIFIER ASSIGN expr error {syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	;
print_stmt: PRINTKW LPAREN expr RPAREN SEMICOLON 
	{
		printf("PARSER : Found  a print statement\n");
		printf("PARSER : Found  a print statement\n");
		$$ = createNode(node_print_stmt);
		$$->print_stmt.expr = $3;
	}
	| PRINTKW expr SEMICOLON 
	{
		printf("PARSER : Found  a print statement\n");
		$$ = createNode(node_print_stmt);
		$$->print_stmt.expr = $2;
	}
	| PRINTKW LPAREN expr RPAREN error {syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	| PRINTKW expr error { syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	;
expr: term 
	{
		$$ = createNode(node_expr);
		$$->expr.left = $1;
	}
	| expr MINUS term 
	{
		printf("PARSER : Found  subtraction expression\n");
		$$ = createNode(node_expr);
		$$->expr.operator = $2;
		$$->expr.left = $1;
		$$->expr.right = $3;
	}
	| expr PLUS term 
	{
		printf("PARSER : Found  addition expression\n");
		$$ = createNode(node_expr);
		$$->expr.operator = $2;
		$$->expr.left = $1;
		$$->expr.right = $3;
	}
	| expr MINUS error {syntaxerrorno++; printf("SYNTAX ERROR : Illegal statement\n");}
	| error MINUS expr	{syntaxerrorno++; printf("SYNTAX ERROR : Illegal statement\n");}
	| expr PLUS error {syntaxerrorno++; printf("SYNTAX ERROR : Illegal statement\n");}
	| error PLUS expr	{syntaxerrorno++; printf("SYNTAX ERROR : Illegal statement\n");}
	;

term: term DIV factor 
	{
		printf("PARSER : Found  division expression\n");
		$$ = createNode(node_term);
		$$->term.term = $1;
		$$->term.operator = $2;
		$$->term.factor = $3;
		
	}
	| term MUL factor 
	{
		printf("PARSER : Found  multiplication expression\n");
		$$ = createNode(node_term);
		$$->term.term = $1;
		$$->term.operator = $2;
		$$->term.factor = $3;
	}
	| factor 
	{
		printf("PARSER : Found  factor\n"); 
		$$ = createNode(node_term); 
		$$->term.factor = $1;
	}
	| error DIV factor {syntaxerrorno++; printf("SYNTAX ERROR : Missing term in expression\n");}
	| error MUL factor {syntaxerrorno++; printf("SYNTAX ERROR : Missing term in expression\n");}
	| term DIV error {syntaxerrorno++; printf("SYNTAX ERROR : Missing factor in expression\n");}
	| term MUL error {syntaxerrorno++; printf("SYNTAX ERROR : Missing factor in expression\n");}
	;
factor: LPAREN expr RPAREN {printf("PARSER : Found  parenthesis-enclosed expression\n");}
	| IDENTIFIER 
	{
		printf("PARSER : Found  identifier\n");
		$$ = createNode(node_factor);
		$$->factor.identifier = $1;
		/*SEMANTIC CHECK*/
		Symbol* symbol = lookupSymbol(symbolTable, $1);
		if(symbol == NULL)
		{
			semerrorno++;
			printf("Ln.%d : SEMANTIC ERROR: Undeclared variable usage : %s\n", yylineno, $1);
		}  else 
		{
			if(symbol->type != NULL)
			{
				insertFactor(head, $1, getSymbolTypeString(symbol->type));
			}
		}
	}
	| number 
	{	
		$$ = createNode(node_factor);
		$$->factor.number = $1;
	}
	;
number: FLOAT 
	{
		printf("PARSER : Found  number - float\n");
		$$ = createNode(node_number);
		$$->number.value = $1;
		insertFactor(head, NULL, $1);
	}
	| INT 
	{
		printf("PARSER : Found  number - int\n");
		$$ = createNode(node_number);
		$$->number.value = $1;
		printf($1); printf($1); printf($1);
		//if(head != NULL) {insertFactor(head, NULL, strdup($1));}
		printf("!!!!");
		
	}
	;
%%

int main(int argc, char** argv) {
	head = (FactorNode*)malloc(sizeof(FactorNode));
	symbolTable = createSymbolTable(30); 
    yyin = fopen(argv[1], "r");  /* Allow for dynamic file input */
    if (!yyin) {
        perror("fopen");
        return 1;
    }
    yyparse();  /* Parse the entire input*/
    fclose(yyin);
	traverseAST(root, 0, ""); /*Print out parse tree*/
	printSymbolTable(symbolTable);
	printf("\n\nCOMPILATION REPORT\nLEXER : Lexical Errors: %d\nPARSER: Syntax Errors: %d\nSEM. ANALYZER: Semantic Errors: %d\n", lexerrorno, syntaxerrorno, semerrorno);
	if(lexerrorno != 0 | syntaxerrorno != 0 | semerrorno != 0)
	{
		printf("\nACTION : Please resolve noted errors before proceeding to code generation ! \n");
	} else 
	{
		printf("Source code is error-free! Continuing to intermediate representation & code generation\n");
	}
	/*Release dynamic memory allocation*/
	deleteAST(root);
	deleteSymbolTable(symbolTable);
	return 0;
}
