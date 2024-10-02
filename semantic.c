#include "semantic.h"
#include <stdio.h>

TAC* tacHead = NULL;
Node* temp_node;
char* temp_string;
Symbol* temp_symbol;

void semanticAnalysis(Node* root, SymbolTable* symbolTable)
{
    if(root == NULL) return;

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
            if(root->stmt.right != NULL)
                semanticAnalysis(root->stmt.right, symbolTable);
            break;
        case node_declaration:
            semanticAnalysis(root->declaration.type,symbolTable);
            break;
        case node_assignment:
            semanticAnalysis(root->assignment.expr, symbolTable);
            break;
        case node_typekw:
            break;
        case node_print_stmt:
            
            semanticAnalysis(root->print_stmt.expr, symbolTable);
            break;
        case node_expr:
            if(root->expr.operator != NULL) {}
            if(root->expr.left != NULL) 
            {
                semanticAnalysis(root->expr.right, symbolTable);
            } 
            if (root->expr.right != NULL) {
                semanticAnalysis(root->expr.right, symbolTable);
            }
            
            /*Symbol* rsym = lookupSymbol(symbolTable, root->expr.right->factor.identifier);
            if(lsym != NULL && rsym != NULL) {
                if(strcmp(getSymbolTypeString(lsym->type), getSymbolTypeString(rsym->type)) != 0) {
                    printf("SEMANTIC ERROR: Type mismatc in expression\n");
                }
            }*/
            break;
        case node_term:
            if (root->term.operator != NULL) {} 
            if (root->term.factor != NULL)
                semanticAnalysis(root->term.factor, symbolTable);
            if (root->term.term != NULL)
                semanticAnalysis(root->term.term, symbolTable);
            break;
        case node_factor:
            if (root->factor.identifier != NULL) {}
            if (root->factor.expr != NULL)
                semanticAnalysis(root->factor.expr, symbolTable);
            if (root->factor.number != NULL)
                semanticAnalysis(root->factor.number, symbolTable);
            break;
        case node_number:
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

