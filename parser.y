%define parse.error verbose

%{
#include "ast.h" /*Parse/AST Tree Management*/
#include "symboltable.h" /*Symbol Table Management*/
#include "semantic.h"
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
%token LPAREN RPAREN LCURLY RCURLY SEMICOLON COMA
%token IDENTIFIER ASSIGN 
%token INT FLOAT 
%token PRINTKW INTKW FLOATKW 


%type <ast> program stmt_list stmt declaration funcdecl assignment print_stmt type term factor number expr
%type <string> IDENTIFIER INTKW FLOATKW FLOAT INT// Specify that IDENTIFIER is of type identifier
%type <operator> ASSIGN MINUS PLUS MUL DIV

%%

program: stmt_list 
{
	$$ = createNode(node_program); /* Begin forming Parse tree/AST*/
	$$->program.stmt_list = $1;
	$$->lineno = yylineno;
	root = $$;
	printf("PARSER : Program successfully parsed\n");
}
	; 

stmt_list: stmt stmt_list 
{
	$$ = createNode(node_stmt_list);
	$$->stmt_list.stmt = $1;
	$$->stmt_list.stmt_list = $2;	
	$$->lineno = yylineno;
	printf("PARSER : Processed statement list\n");
}
	| 
	{
		 /*empty*/ $$ = createNode(node_stmt_list);
		$$->lineno = yylineno; 
	}
	;
stmt: declaration 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| funcdecl
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| assignment  
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| print_stmt 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| expr SEMICOLON 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| expr error {syntaxerrorno++; printf("Ln.%d : SYNTAX ERROR : MISSING SEMICOLON\n", lnolastid);}

	;
declaration: type IDENTIFIER SEMICOLON 
	{
		printf("PARSER : Found  declaration\n");
		$$ = createNode(node_declaration);
		$$->declaration.type = $1;
		$$->declaration.identifier = $2;
		$$->lineno = lnolastid;
	}
	| type IDENTIFIER error {syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	;

funcdecl: type IDENTIFIER LPAREN funcargs RPAREN  SEMICOLON
	{
		printf("PARSER : Found function declaration\n");
		$$ = createNode(node_funcdecl);
		$$->funcdecl.type = $1;
		$$->funcdecl.identifier = $2;
		$$->funcdecl.args = $4;
		$$->lineno = yylineno;

	}
	;
funcargs: paramlist 
	{
		printf("Found funcargs");
		$$ = createNode(node_funcargs);
		$$->funcargs.paramlist = $1;
		$$->lineno = yylineno;
	}
	| {/* empty argument possible*/}
	;
paramlist: paramlist COMA param
	{
		printf("Found paramlist");
		$$ = createNode(node_paramlist);
		$$->paramlist.paramlist = $1;
		$$->param = $3; 
		$$->lineno = yylineno;
	}
	| param
	{
		printf("Found paramlist");
		$$ = createNode(node_param);
		$$->paramlist.param = $1;
		$$->lineno = yylineno;
	}
	;
param: type IDENTIFIER 
	{
		printf("Found param");
		$$ = createNode(node_param);
		$$->param.type = $1;
		$$->param.identifier = $2;
		$$->lineno = yylineno;
	}
	;
type: FLOATKW
	{
		$$ = createNode(node_typekw);
		$$->typekw.type = $1;
		$$->lineno = yylineno;
	}
	| INTKW 
	{
		$$ = createNode(node_typekw);
		$$->typekw.type = $1;
		$$->lineno = yylineno;
	}
	;
assignment: IDENTIFIER ASSIGN expr SEMICOLON 
{
	$$ = createNode(node_assignment);
	$$->assignment.identifier = $1;
	$$->assignment.assign = $2;
	$$->assignment.expr = $3;
	$$->lineno = yylineno;
}
	| IDENTIFIER ASSIGN expr error {syntaxerrorno++; printf("Ln.%d : PARSER : SYNTAX ERROR : MISSING SEMICOLON\n", yylineno);}
	| IDENTIFIER ASSIGN error SEMICOLON {syntaxerrorno++; printf("SYNTAX ERROR : Missing assignment arg.");}
	;
print_stmt: PRINTKW LPAREN expr RPAREN SEMICOLON 
	{
		printf("PARSER : Found  a print statement\n");
		printf("PARSER : Found  a print statement\n");
		$$ = createNode(node_print_stmt);
		$$->print_stmt.expr = $3;
		$$->lineno = yylineno;
	}
	| PRINTKW expr SEMICOLON 
	{
		printf("PARSER : Found  a print statement\n");
		$$ = createNode(node_print_stmt);
		$$->print_stmt.expr = $2;
		$$->lineno = yylineno;
	}
	| PRINTKW LPAREN expr RPAREN error {syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	| PRINTKW expr error { syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
	;
expr: term 
	{
		$$ = createNode(node_expr);
		$$->expr.left = $1;
		$$->lineno = yylineno;
	}
	| expr MINUS term 
	{
		printf("PARSER : Found  subtraction expression\n");
		$$ = createNode(node_expr);
		$$->expr.operator = $2;
		$$->expr.left = $1;
		$$->expr.right = $3;
		$$->lineno = yylineno;
	}
	| expr PLUS term 
	{
		printf("PARSER : Found  addition expression\n");
		$$ = createNode(node_expr);
		$$->expr.operator = $2;
		$$->expr.left = $1;
		$$->expr.right = $3;
		$$->lineno = yylineno;
	}
	| expr MINUS error {syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
	| error MINUS term	{syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
	| expr PLUS error {syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
	| error PLUS term	{syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
	;

term: term DIV factor 
	{
		printf("PARSER : Found  division expression\n");
		$$ = createNode(node_term);
		$$->term.term = $1;
		$$->term.operator = $2;
		$$->term.factor = $3;
		$$->lineno = yylineno;
		
	}
	| term MUL factor 
	{
		printf("PARSER : Found  multiplication expression\n");
		$$ = createNode(node_term);
		$$->term.term = $1;
		$$->term.operator = $2;
		$$->term.factor = $3;
		$$->lineno = yylineno;
	}
	| factor 
	{
		printf("PARSER : Found  factor\n"); 
		$$ = createNode(node_term); 
		$$->term.factor = $1;
		$$->lineno = yylineno;
	}
	| error DIV factor {syntaxerrorno++; printf("Ln.%d : SYNTAX ERROR : Missing term in expression\n", yylineno);}
	| error MUL factor {syntaxerrorno++; printf("Ln.%d :SYNTAX ERROR : Missing term in expression\n", yylineno);}
	| term DIV error {syntaxerrorno++; printf("Ln.%d :SYNTAX ERROR : Missing factor in expression\n", yylineno);}
	| term MUL error {syntaxerrorno++; printf("Ln.%d :SYNTAX ERROR : Missing factor in expression\n", yylineno);}
	;
factor: LPAREN expr RPAREN 
	{
	printf("PARSER : Found  parenthesis-enclosed expression\n");
	$$ = createNode(node_factor);
	$$->lineno = yylineno;
	$$->factor.expr = $2;
	}
	| IDENTIFIER 
	{
		printf("PARSER : Found  identifier\n");
		$$ = createNode(node_factor);
		$$->factor.identifier = $1;
		$$->lineno = yylineno;
	}
	| number 
	{	
		$$ = createNode(node_factor);
		$$->factor.number = $1;
		$$->lineno = yylineno;
	}
	;
number: FLOAT 
	{
		printf("PARSER : Found  number - float\n");
		$$ = createNode(node_number);
		$$->number.value = $1;
		$$->number.type = "float";
		$$->lineno = yylineno;
	}
	| INT 
	{
		printf("PARSER : Found  number - int\n");
		$$ = createNode(node_number);
		$$->number.value = $1;
		$$->number.type = "int";
		$$->lineno = yylineno;
	}
	;
%%

int main(int argc, char** argv) {
	symbolTable = createSymbolTable(100); 
    yyin = fopen(argv[1], "r");  /* Allow for dynamic file input */
    if (!yyin) {
        perror("fopen");
        return 1;
    }
    yyparse();  /* Parse the entire input*/
    fclose(yyin);
	traverseAST(root, 0, ""); /*Print out parse tree*/
	
	semanticAnalysis(root, symbolTable);
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
