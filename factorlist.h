#ifndef FACTORLIST_H
#define FACTORLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symboltable.h"

extern int yylineno;

typedef struct FactorNode {
    char* identifier;       /* Store identifier of the factor */
    char* type;             /* Store the type of the factor as a string */
    struct FactorNode* next; /* Next factor in the list */
} FactorNode; /* Linked list to keep track of factors in expression */

void insertFactor(FactorNode* head, char* identifier, char* type); 
void checkFactorTypes(FactorNode* head);
// Free up the list after use
void deleteFactorList(FactorNode* head);

#endif
