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

extern TAC* tacHead; 
extern int semerrorno;
void semanticAnalysis(Node*, SymbolTable* symbolTable);
int checkTypeCompatibility(const char* type1, const char* type2);
TAC* generateTAC(Node* node);
;
#endif