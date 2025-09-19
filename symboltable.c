#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
//
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"
#define BLUE "\x1b[34m"
#define PINK "\x1b[35m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"

DataType getSymbolType(const char* dataType)
{
    if(strcmp(dataType, "int") == 0)
    {
        return type_int;
    } else if(strcmp(dataType, "float") == 0)
    {
        return type_float;
    } else 
    {
        return type_unknown;
    }

}

char* getSymbolTypeString(DataType dataType)
{
    switch(dataType)
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

char* getScopeTypeString(Scope scope)
{
    switch(scope)
    {
    case(local):
        return "local";
        break;
    case(global):
        return "global";
        break;
    default:
        return "unknown";
        break;
    }
}

char* getDeclTypeString(DeclType declType)
{
    switch(declType)
    {
    case(decl_var):
        return "Variable";
        break;
    case(decl_func):
        return "Function";
        break;
    case(decl_param):
        return "Parameter";
        break;
    case(decl_const):
        return "Constant";
        break;
    default:
        return "unknown";
        break;
    }
}
/*
// Hash func. to index identifier strings
static unsigned int hash(const char* str, int size)
{
    unsigned int hash = 0;
    while(*str)
    {
        hash = (hash <<  5) + *str++;
    }
    return hash % size;
}
*/

static unsigned int scopeHash(const char* identifier, const Symbol* parentScope, int size)
{
    unsigned int hash = 0;
    while(*identifier)
    {
        hash = (hash << 5) + *identifier++;
    }

    // If non-global-scope, incorporate parent scope into hash
    if (parentScope != NULL)
    {
         const char* parentIdentifier = parentScope->identifier;
        while (*parentIdentifier)
        {
            hash = (hash << 5) + *parentIdentifier++;
        }
    }

    
    return hash % size;
}
SymbolTable* createSymbolTable(int size)
{
    SymbolTable* table = malloc(sizeof(SymbolTable));
    table->size = size;
    table->table = calloc(size, sizeof(Symbol*));
}

void insertSymbol(SymbolTable* table, const Symbol* currentScope, const char* identifier, char* dataType, DeclType declType, int lineno)
{
    unsigned int index = scopeHash(identifier, currentScope, table->size);
    Symbol* newEntry = malloc(sizeof(Symbol));
    if (newEntry == NULL) { return; }
    
    strncpy(newEntry->identifier, identifier, MAX_IDENT_LEN);
    newEntry->dataType = getSymbolType(dataType);
    newEntry->lineno = lineno;
    newEntry->declType = declType;
    if(currentScope != NULL){newEntry->scope = local;} else  {newEntry->scope = global;}
    newEntry->parent_scope = currentScope; // Parent scope is the function in which the symbol is declared (only function support currently)
    newEntry->next = table->table[index];
    table->table[index] = newEntry;
}

Symbol* lookupSymbol(SymbolTable* table, const Symbol* currentScope, const char* identifier)
{
    if (table == NULL || table->table == NULL) {
        printf("Error: Symbol table is not initialized\n");
        return NULL;
    }
    unsigned int index = scopeHash(identifier, currentScope, table->size);
    Symbol* symbol = table->table[index];
    return symbol;
}
void printSymbolTable(SymbolTable* table)
{
    // Table header
    printf("|| SYMBOL TABLE ||\n");
    printf( "| %-10s | %-10s | %-10s | %-10s | %-10s | %-10s |\n", 
           "Type", "Parent Scope", "Scope Type", "Data Type", "Name", "Line No.");

    // Iterate over the symbol table
    for (int i = 0; i < table->size; i++)
    {
        Symbol* symbol = table->table[i];
        while (symbol != NULL)
        {
            if (symbol->parent_scope == NULL)
            {
                // No parent scope: Print "N/A" for parent scope fields
                printf("| %-10s | %-10s | %-10s | %-10s | %-10s | %-10d |\n", 
                    getDeclTypeString(symbol->declType), 
                    "N/A", 
                    getScopeTypeString(symbol->scope), 
                    getSymbolTypeString(symbol->dataType), 
                    symbol->identifier, 
                    symbol->lineno);
            } 
            else 
            {

                char parentInfo[61];
                snprintf(parentInfo, sizeof(parentInfo), "%s %s", getDeclTypeString(symbol->parent_scope->declType), symbol->parent_scope->identifier);
                printf("| %-10s | %-10s | %-10s | %-10s | %-10s | %-10d |\n", 
                    getDeclTypeString(symbol->declType), 
                    parentInfo, 
                    getScopeTypeString(symbol->scope), 
                    getSymbolTypeString(symbol->dataType), 
                    symbol->identifier, 
                    symbol->lineno);
            }
            symbol = symbol->next;  // Move to the next symbol in the chain
        }
    }
    
}

void printSymbol(Symbol* symbol)
{
    if (symbol == NULL) {
        printf("Symbol is NULL\n");
        return;
    }
    printf("Symbol: %s\n", symbol->identifier);
    printf("Data Type: %s\n", getSymbolTypeString(symbol->dataType));
    printf("Scope: %s\n", getScopeTypeString(symbol->scope));
    printf("Parent Scope: %s\n", symbol->parent_scope->identifier);
    printf("Declaration Type: %s\n", getDeclTypeString(symbol->declType));
    printf("Line No.: %d\n", symbol->lineno);
}


// Delete symbol table
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
