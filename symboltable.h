#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define MAX_IDENT_LEN 64 // Max. Identifier Length, enforced by lexer.l ruleset

// Symbol Table implemented as a linked list


typedef enum 
{
    type_int,
    type_float,
    type_unknown,
} DataType; // Possible Variable Data Types - Tokens (Var declarations and function returns)

typedef enum 
{
    local,
    global,
} Scope; // Declaration Scope

typedef enum 
{
    decl_var,
    decl_func,
    decl_param,
    decl_const,
    decl_unknown,
} DeclType; // Declaration Type

// Struct defining SymbolTable entry
typedef struct Symbol {
    char identifier[MAX_IDENT_LEN];
    DataType dataType;
    DeclType declType;
    struct Symbol* next;
    int lineno;
    Scope scope;
    struct Symbol* parent_scope;  // points to function (if null, then global)
} Symbol;

typedef struct SymbolTable 
{
    Symbol **table; // Hash table array of pointers
    int size; // No. Entries in Table
} SymbolTable;

// Function Declarations
SymbolTable* createSymbolTable(int size);
void insertSymbol(SymbolTable* table, const Symbol* currentScope, const char* identifier, char* dataType, DeclType declType, int lineno);
Symbol* lookupSymbol(SymbolTable* table, const Symbol* currentScope, const char* identifier);
void printSymbolTable(SymbolTable* table);
void deleteSymbolTable(SymbolTable* table); // Trash collection
char* getScopeTypeString(Scope scope);
char* getSymbolTypeString(DataType dataType);
char* getDeclTypeString(DeclType declType);

#endif