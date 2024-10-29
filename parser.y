%define parse.error verbose

%{
#include "ast.h" // Parse/AST Tree Management
#include "symboltable.h" /*Symbol Table Management*/
#include "semantic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int yylineno; // Declared in lexer
extern char* yytext;
extern int lexerrorno;
int semerrorno = 0; 
int syntaxerrorno = 0;
extern int yylex();
extern int yyparse();
extern void yyerror(); 
extern FILE* yyin;
extern int lnolastid; // Symbol table util
struct Node* root = NULL; // AST Root Node
struct SymbolTable* symbolTable = NULL;

struct FactorNode* head = NULL;

%}

%union 
{
	struct Node* ast; // Each rule will return an AST node 
    struct SymbolTable* st;
	struct Symbol* symbol;
	char* string; 
	char* operator;
}
%token PLUS MINUS MUL DIV
%token LPAREN RPAREN LCURLY RCURLY SEMICOLON COMA LBRACKET RBRACKET
%token IDENTIFIER ASSIGN 
%token INT FLOAT 
%token PRINTKW INTKW FLOATKW RETURNKW


%type <ast> program stmt_list stmt declaration var_decl func_call func_def return_stmt array_decl array_def array_index expr_list func_args arg_list arg func_decl func_params param_list param assignment print_stmt type term factor number expr 
%type <string> IDENTIFIER INTKW FLOATKW FLOAT INT 
%type <operator> ASSIGN MINUS PLUS MUL DIV

%%

program: stmt_list 
{
	$$ = createNode(node_program); // Begin forming Parse tree/AST 
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
		$$ = createNode(node_stmt_list); // If statement list is empty 
		$$->lineno = yylineno; 
	}
	;
stmt: var_decl SEMICOLON
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| func_def 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| func_decl
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| func_call 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| array_decl
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
	| return_stmt 
	{
		$$ = createNode(node_stmt);
		$$->stmt.right = $1;
		$$->lineno = yylineno;
	}
	| expr error {syntaxerrorno++; printf("Ln.%d : SYNTAX ERROR : MISSING SEMICOLON\n", lnolastid);}
	;

array_decl: declaration LBRACKET expr RBRACKET SEMICOLON
{
	printf("Found array decl\n");
	$$ = createNode(node_array_decl);
	$$->array_decl.decl = $1;
	$$->array_decl.size = $3;
	$$->lineno = yylineno;
}
;

declaration: type IDENTIFIER
	{
		printf("PARSER : Found  declaration\n");
		$$ = createNode(node_declaration);
		$$->declaration.type = $1;
		$$->declaration.identifier = $2;
		$$->lineno = lnolastid;
	}
	;

var_decl: declaration 
	;
	
func_def: declaration LPAREN func_params RPAREN LCURLY stmt_list RCURLY 
	{
		printf("Found function definition\n");
		$$ = createNode(node_func_def);
		$$->func_def.decl = $1;
		$$->func_def.params = $3; 
		$$->func_def.stmt_list = $6;
		$$->lineno = yylineno;
	}
	;
func_decl: declaration LPAREN func_params RPAREN SEMICOLON
	{
		printf("PARSER : Found function declaration\n");
		$$ = createNode(node_func_decl);
		$$->func_decl.decl = $1;
		$$->func_decl.params = $3;
		$$->lineno = yylineno;
	}
	;
func_params: param_list 
	{
		printf("Found func_params\n");
		$$ = createNode(node_func_params);
		$$->func_params.param_list = $1;
		$$->lineno = yylineno;
	}
	| 
	{
		printf("Found func_params\n");
		$$ = createNode(node_func_params);
		$$->lineno = yylineno;
	} // empty argument possible
	;
param_list: param_list COMA param
	{	// Multiple parameters
		printf("Found param_list\n");
		$$ = createNode(node_param_list);
		$$->param_list.param_list = $1;
		$$->param_list.param = $3; 
		$$->lineno = yylineno;
	} 
	| param
	{
		// Single parameter
		printf("Found param_list\n");
		$$ = createNode(node_param_list);
		$$->param_list.param_list = $1;
		$$->lineno = yylineno;
	}
	;
param: type IDENTIFIER 
	{
		printf("Found param\n");
		$$ = createNode(node_param);
		$$->param.type = $1;
		$$->param.identifier = $2;
		$$->lineno = yylineno;
	}
	;
func_call: IDENTIFIER LPAREN func_args RPAREN SEMICOLON
	{
		printf("Found function call\n");
		$$ = createNode(node_func_call);
		$$->func_call.identifier = $1;
		$$->func_call.args = $3;
		$$->lineno = yylineno;
	}
	;
func_args: arg_list
	{
		printf("Found function args\n");
		$$ = createNode(node_func_args);
		$$->func_args.arg_list = $1;
		$$->lineno = yylineno;
	}
	| 
	{
		printf("Found function args\n");
		$$ = createNode(node_func_args);
		$$->lineno = yylineno;
	} 
	;
arg_list: arg_list COMA arg 
	{
		// Multiple args
		printf("Found arg list\n");
		$$ = createNode(node_arg_list);
		$$->arg_list.arg_list = $1;
		$$->arg_list.arg = $3;
		$$->lineno = yylineno;
	}
	| arg
	{
		// Single arg
		printf("Found arg list\n");
		$$ = createNode(node_arg_list);
		$$->arg_list.arg = $1;
		$$->lineno = yylineno;
	}
	;
arg: expr
	{
		printf("Found arg\n");
		$$ = createNode(node_arg);
		$$->arg.expr = $1;
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
assignment: var_decl ASSIGN expr SEMICOLON
	{	
		$$ = createNode(node_assignment);
		$$->assignment.assignee = $1;
		$$->assignment.assign = $2;
		$$->assignment.expr = $3;
		$$->lineno = yylineno;
	}
	| IDENTIFIER ASSIGN expr SEMICOLON 
	{
		$$ = createNode(node_assignment);
		$$->assignment.identifier = $1;
		$$->assignment.assign = $2;
		$$->assignment.expr = $3;
		$$->lineno = yylineno;
	}
	| IDENTIFIER ASSIGN expr error {syntaxerrorno++; printf("Ln.%d : PARSER : SYNTAX ERROR : MISSING SEMICOLON\n", yylineno);}
	| IDENTIFIER ASSIGN error SEMICOLON {syntaxerrorno++; printf("SYNTAX ERROR : Missing assignment arg.");}
	| array_index ASSIGN expr SEMICOLON
	{
		$$ = createNode(node_assignment);
		$$->assignment.assignee = $1;
		$$->assignment.assign = $2;
		$$->assignment.expr = $3;
		$$->lineno = yylineno;
	}
	;
print_stmt: PRINTKW LPAREN expr RPAREN SEMICOLON 
	{
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
return_stmt: RETURNKW expr SEMICOLON
	{
		printf("Found return statement");
		$$ = createNode(node_return_stmt);
		$$->return_stmt.expr = $2;
		$$->lineno = yylineno;
	}
	;

expr: term 
	{
		$$ = createNode(node_expr);
		$$->expr.left = $1;
		$$->lineno = yylineno;
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
	| array_index 
	{
		printf("PARSER : Found  array_index expression\n");
		$$ = createNode(node_expr);
		$$->expr.right = $1;
		$$->lineno = yylineno;
	}	
	;

array_index: IDENTIFIER LBRACKET expr RBRACKET
{
	printf("PARSER: Found array_index\n");
	$$ = createNode(node_array_index);
	$$->array_index.identifier = $1;
	$$->array_index.index = $3;
	$$->lineno = yylineno;
}
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
    yyin = fopen(argv[1], "r");  // Allow for dynamic file input 
    if (!yyin) {
        perror("fopen");
        return 1;
    }
    yyparse();  // Parse the entire input
    fclose(yyin);
	traverseAST(root, 0, ""); // Print out parse tree
	
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

	// Release dynamic memory allocation
	
	deleteAST(root);
	deleteSymbolTable(symbolTable);
	return 0;
}
