#ifndef CODE_OPTIMIZER_H
#define CODE_OPTIMIZER_H

#include "ast.h" // Include ast.h to get the Node struct
#include "symboltable.h" // Include symboltable.h to get the SymbolTable struct
#include "semantic.h" // Include semantic.h to get the TAC struct

// Function to perform code optimization on ntermediate code
void codeOptimization(TAC* head);

#endif // CODE_OPTIMIZER_H