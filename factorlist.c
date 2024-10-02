#include "factorlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symboltable.h"

void insertFactor(FactorNode* head, char* identifier, char* type)
{
    FactorNode* newNode = (FactorNode*)malloc(sizeof(FactorNode));
    newNode->identifier = strdup(identifier);
    newNode->type = strdup(type);
    newNode->next = head;
    head = newNode;  // Update the head to point to the new node
}

void checkFactorTypes(FactorNode* head)
{
    if (!head) return;

    FactorNode* current = head;
    char* firstType = head->type;

    while (current != NULL) {
        if (strcmp(current->type, firstType) != 0) {
            printf("Ln.%d: SEMANTIC ERROR: Type mismatch in expression\n", yylineno);
            break;
        }
        current = current->next;
    }
}

// Free up the list after use
void deleteFactorList(FactorNode* head)
{
    FactorNode* current = head;
    FactorNode* next;
    while (current != NULL) {
        next = current->next;
        free(current->identifier);
        free(current->type);
        free(current);
        current = next;
    }
    head = NULL;  // Reset the head
}