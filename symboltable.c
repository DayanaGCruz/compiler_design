#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

VarType getSymbolType(const char* type)
{
    VarType var_type;
    if(strcmp(type, "int") == 0)
    {
        return type_int;
    } else if(strcmp(type, "float") == 0)
    {
        return type_float;
    } else 
    {
        return type_unknown;
    }

}

char* getSymbolTypeString(VarType type)
{
    switch(type)
    {
    case(type_int):
        return "int";
        break;
    case(type_float):
        return "float";
        break;
    default:
        return "unknown";
        break;
    }
}

/* Hash func. to index identifier strings*/
static unsigned int hash(const char* str, int size)
{
    unsigned int hash = 0;
    while(*str)
    {
        hash = (hash <<  5) + *str++;
    }
    return hash % size;
}

SymbolTable* createSymbolTable(int size)
{
    SymbolTable* table = malloc(sizeof(SymbolTable));
    table->size = size;
    table->table = calloc(size, sizeof(Symbol*));
}

void insertSymbol(SymbolTable* table, const char* identifier, char* type, int lineno)
{
    unsigned int index = hash(identifier, table->size);
    Symbol* newEntry = malloc(sizeof(Symbol));
    if (newEntry == NULL)
    { return; }
    strncpy(newEntry->identifier, identifier, MAX_IDENT_LEN);
    newEntry->type = getSymbolType(type);
    newEntry->lineno = lineno;
    newEntry->next = table->table[index];
    table->table[index] = newEntry;
}

Symbol* lookupSymbol(SymbolTable* table, const char* identifier)
{
    if (table == NULL || table->table == NULL) {
        printf("Error: Symbol table is not initialized\n");
        return NULL;
    }
    unsigned int index = hash(identifier, table->size);
    Symbol* symbol = table->table[index];
    while(symbol != NULL)
    {
        if(strncmp(symbol->identifier, identifier, MAX_IDENT_LEN) == 0)
        {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}

void printSymbolTable(SymbolTable* table)
{
    printf("|| SYMBOL TABLE ||\n");
    printf("======================================================================\n");
    printf("| %-10s | %-20s | %-30s |\n", "Type", "Identifier", "Line No.");
    printf("======================================================================\n");
    
    for (int i = 0; i < table->size; i++)
    {
        Symbol* symbol = table->table[i];
        
        while (symbol != NULL)
        {
            // Print each symbol in the current index with proper formatting
            printf("| %-10s | %-20s | %-30d |\n", getSymbolTypeString(symbol->type), symbol->identifier, symbol->lineno);
            symbol = symbol->next;  // Move to the next symbol in the chain
        }
    }
    printf("======================================================================\n");
}

/* Delete symbol table*/
void deleteSymbolTable(SymbolTable* table){
    for(int i = 0; i < table->size; i++)
    {
        Symbol* symbol = table->table[i];
        while(symbol != NULL) 
        {
            Symbol* nextSymbol = symbol->next;
            free(symbol);
            symbol = nextSymbol;
        }
    }
    free(table->table);
    free(table);
}