#include "semantic.h"
#include <stdio.h>

TAC* tacHead = NULL;
Node* temp_node;
char* temp_string;
Symbol* sym; /* temp symbol pointer*/
char* lExprType;
char* rExprType;
void semanticAnalysis(Node* root, SymbolTable* symbolTable)
{
    if(root == NULL) return;
    sym = NULL; /*Reset temp symbol*/
    switch (root->nodeType) 
    {
        case node_program:
            printf("SEMANTIC ANALYSIS\n");
            semanticAnalysis(root->program.stmt_list, symbolTable);
            break; 
        case node_stmt_list:
            if(root->stmt_list.stmt != NULL) 
                semanticAnalysis(root->stmt_list.stmt, symbolTable);
            if(root->stmt_list.stmt_list != NULL) 
                semanticAnalysis(root->stmt_list.stmt_list, symbolTable);
            break;
        case node_stmt:
            printf("IN STMT\n");
            if(root->stmt.right != NULL)
                semanticAnalysis(root->stmt.right, symbolTable);
            break;
        case node_declaration:
            printf("IN DECLARATION\n");
            sym = lookupSymbol(symbolTable, root->declaration.identifier);
            printf("IDENTIFIER: %s\n", root->declaration.identifier);
            if(sym != NULL) {
                semerrorno++;
                if(root->lineno != NULL && root->declaration.identifier != NULL && sym->lineno != NULL)
                {
                    printf("Ln.%d : SEMANTIC ERROR: Duplicate variable declaration : Identifier %s already declared on line %d\n", root->lineno ,root->declaration.identifier, sym->lineno);
                }    
            } else {
                printf("INSERTING SYMBOL\n");
                if(root->declaration.type->typekw.type != NULL && root->declaration.identifier != NULL && root->lineno != NULL) 
                {
                    insertSymbol(symbolTable, root->declaration.identifier, root->declaration.type->typekw.type, root->lineno);
                }
            }
            semanticAnalysis(root->declaration.type,symbolTable);
            break;
        case node_assignment:
        printf("IN ASSIGNMENT\n");
            sym = lookupSymbol(symbolTable, root->assignment.identifier);
            if(sym == NULL) {
                semerrorno++;
                printf("Ln.%d. SEMANTIC ERROR: Undeclared variable reference : Variable %s not declared\n", root->lineno, root->assignment.identifier);
            }
            printf("ASSIGNMENT IDENTIFIER: %s\n", root->assignment.identifier);
            semanticAnalysis(root->assignment.expr, symbolTable);
            break;
        case node_typekw:
            break;
        case node_print_stmt:
            printf("IN PRINT STMT\n");
            semanticAnalysis(root->print_stmt.expr, symbolTable);
            break;
        case node_expr:
            printf("IN EXPR\n");
            if(root->expr.left != NULL) 
            {
                semanticAnalysis(root->expr.left, symbolTable);
            }
            if (root->expr.right != NULL) {
                semanticAnalysis(root->expr.right, symbolTable);
            }
            if(root->expr.left != NULL && root->expr.right != NULL) {
                printf("LEFT TYPE: %s\n", lExprType);
                printf("RIGHT TYPE: %s\n", rExprType);
                if(!checkTypeCompatibility(lExprType, rExprType)) {
                    semerrorno++;
                    printf("Ln.%d SEMANTIC ERROR: Type mismatch : Incompatible types %s and %s\n", root->lineno, lExprType, rExprType);
                }
                lExprType = NULL;
                rExprType = NULL;
            }
            break;
        case node_term:
        printf("IN TERM\n");
            if (root->term.operator != NULL) {} 
            if (root->term.factor != NULL)
                semanticAnalysis(root->term.factor, symbolTable);
            if (root->term.term != NULL)
                semanticAnalysis(root->term.term, symbolTable);
            break;
        case node_factor:
            printf("IN FACTOR\n");
            if (root->factor.identifier != NULL) 
            {
                printf("IN FACTOR IDENTIFIER\n");
                sym = lookupSymbol(symbolTable, root->factor.identifier);
                if(sym == NULL) {
                    semerrorno++;
                    printf("Ln.%d SEMANTIC ERROR: Undeclared variable reference : Variable %s not declared\n", root->lineno, root->factor.identifier);
                } else 
                {
                    if(lExprType == NULL)
                    {
                        lExprType = getSymbolTypeString(sym->type);
                    }
                    else if(rExprType == NULL) {
                        rExprType = getSymbolTypeString(sym->type);
                    }
                }
            }
            if (root->factor.expr != NULL){
                printf("IN FACTOR EXPR\n");
                semanticAnalysis(root->factor.expr, symbolTable);
            }
            if (root->factor.number != NULL){
                printf("IN FACTOR NUMBER\n");
                semanticAnalysis(root->factor.number, symbolTable);
            }
            break;
        case node_number:           
            printf("IN NUMBER\n");
            printf("Value: %s\n", root->number.value);
             if(lExprType == NULL)
                {
                   lExprType = root->number.type;
                }
                else if(rExprType == NULL) {
                    rExprType = root->number.type;
                    
                }
            break;
        default:
            printf("Unknown Node\n");
            break;
    }

}

TAC* generateTAC(Node* node)
{
    if (node == NULL) return NULL;
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if(!instruction) return NULL;

    switch (node->nodeType)
    {
    case node_expr:       
        break;
    case node_declaration:
        break;
    case node_assignment:
        break;
    case node_print_stmt:
        break;
    default:
        free(instruction);
        return NULL;
    }

    instruction->next = NULL;
    //appendTAC(&tacHead, instruction);
    return instruction;
}

int checkTypeCompatibility(const char* type1, const char* type2)
{
    if (strcmp(type1, type2) == 0) return 1; 
    else {return 0;} 
}

