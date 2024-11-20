#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symboltable.h"

typedef struct 
{
    char* op;
    char* arg1;
    char* arg2;
    char* result;
    struct TAC* next; 
}TAC;

typedef struct
{
    char* data[100];
    int top;
} Stack;


extern TAC* tacHead; 
extern int semerrorno;
void semanticAnalysis(Node*, SymbolTable* symbolTable);
int checkTypeCompatibility(const char* type1, const char* type2);
TAC* generateTAC(Node* root);
TAC* createTAC(char* op, char* arg1, char* arg2);
void printTAC(TAC* tac);
Stack* createStack();
void push(Stack* stack, char* value);
char* pop(Stack* stack);
int stackSize (Stack* stack);
int isEmpty(Stack* stack);
#endif