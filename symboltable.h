#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define MAX_IDENT_LEN 64 /* Max. Identifier Length, enforced by lexer.l ruleset*/

/* Symbol Table implemented as a linked list*/


typedef enum 
{
    type_int,
    type_float,
    type_unknown,
} VarType; /* Possible Variable Data Types - Tokens*/

/* Struct defining SymbolTable entry*/
typedef struct Symbol {
    char identifier[MAX_IDENT_LEN];
    VarType type;
    struct Symbol* next;
    int line;
} Symbol;

typedef struct SymbolTable 
{
    Symbol **table; /* Hash table array of pointers*/
    int size; /* No. Entries in Table*/
} SymbolTable;

/* Function Declarations*/
SymbolTable* createSymbolTable(int size);
void insertSymbol(SymbolTable* table, const char* identifier, char* type, int line);
Symbol* lookupSymbol(SymbolTable* table, const char* identifier);
void printSymbolTable(SymbolTable* table);
void deleteSymbolTable(SymbolTable* table); /* Trash collection*/
VarType getSymbolType(const char* type);
char* getSymbolTypeString(VarType type);

#endif