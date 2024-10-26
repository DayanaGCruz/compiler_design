#include "semantic.h"
#include <stdio.h>

TAC* tacHead = NULL;
Node* temp_node;
char* temp_string;
Symbol* sym; // temp symbol pointer
char* lExprType;
char* rExprType;
Symbol* currentScope;
char* temp_dataType;
char* temp_identifier;

void semanticAnalysis(Node* root, SymbolTable* symbolTable)
{
    if(root == NULL) return;
    sym = NULL; //Reset temp symbol
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
            sym = lookupSymbol(symbolTable,  currentScope, root->declaration.identifier);
            printf("IDENTIFIER: %s\n", root->declaration.identifier);
            printf(sym->identifier);
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
                    insertSymbol(symbolTable, currentScope, root->declaration.identifier, root->declaration.type->typekw.type, decl_var, root->lineno);
                }
            }
            semanticAnalysis(root->declaration.type,symbolTable);
            break;
        case node_func_decl:
            printf("IN FUNC DECL\n");
            temp_dataType = root->func_decl.decl->declaration.type->typekw.type;
            temp_identifier = root->func_decl.decl->declaration.identifier;
            sym = lookupSymbol(symbolTable,  currentScope, root->func_decl.decl->declaration.identifier);
            if(sym != NULL) 
            {
                if(sym->scope == local && sym->parent_scope->identifier == currentScope->parent_scope->identifier)
                {
                    semerrorno++;
                    if(root->lineno != NULL && temp_identifier != NULL && sym->lineno != NULL)
                    {
                        printf("Ln.%d : SEMANTIC ERROR: Duplicate function declaration : Identifier %s already declared on line %d\n", root->lineno ,temp_identifier, sym->lineno);
                        
                    }   
                }
            } else 
            {
                if(temp_dataType != NULL && temp_identifier != NULL && root->lineno != NULL) 
                {
                    insertSymbol(symbolTable, currentScope, temp_identifier, temp_dataType, decl_func, root->lineno);
                }
                currentScope = lookupSymbol(symbolTable, currentScope, temp_identifier);
                semanticAnalysis(root->func_decl.decl, symbolTable);
                semanticAnalysis(root->func_decl.params, symbolTable);
                currentScope = NULL;
                printf("CURRENT SCOPE CHECK2: %s\n", currentScope->identifier);
            }
            break;
        case node_func_params:
            printf("IN FUNC PARAMS\n");
            if(root->func_params.param_list != NULL) 
                semanticAnalysis(root->func_params.param_list, symbolTable);
            break;
        case node_param_list:
            printf("IN PARAM LIST\n");
            if(root->param_list.param != NULL) 
                semanticAnalysis(root->param_list.param, symbolTable);
            if(root->param_list.param_list != NULL) 
                semanticAnalysis(root->param_list.param_list, symbolTable);
            break;
        case node_param:
            printf("IN PARAM\n");
            printf("Current scope: %s\n", currentScope->identifier);
            sym = lookupSymbol(symbolTable,  currentScope, root->param.identifier);
            if(sym != NULL) 
            {
                if(sym->parent_scope->identifier != currentScope->identifier)
                {
                    semerrorno++;
                    if(root->lineno != NULL && root->param.identifier != NULL && sym->lineno != NULL)
                    {
                        printf("Ln.%d : SEMANTIC ERROR: Duplicate parameter declaration : Identifier %s already declared on line %d\n", root->lineno ,root->param.identifier, sym->lineno);
                    }   
                } 
            } else {
                if(root->param.type->typekw.type != NULL && root->param.identifier != NULL && root->lineno != NULL) 
                {
                    insertSymbol(symbolTable,  currentScope, root->param.identifier, root->param.type->typekw.type, decl_param, root->lineno);
                }
            }
            break;
        case node_func_call:
            printf("IN FUNC CALL\n");
            printf("CURRENT SCOPE CHECK: %s\n", currentScope->identifier);
            sym = lookupSymbol(symbolTable,  currentScope, root->func_call.identifier);
            if(sym == NULL) {
                semerrorno++;
                printf("Ln.%d. SEMANTIC ERROR: Undeclared function reference : Function %s not declared\n", root->lineno, root->func_call.identifier);
            }
            break;
        case node_func_args:
            printf("IN FUNC ARGS\n");
            if(root->func_args.arg_list != NULL) 
                semanticAnalysis(root->func_args.arg_list, symbolTable);
            break;
        case node_arg_list:
            printf("IN ARG LIST\n");
            if(root->arg_list.arg != NULL) 
                semanticAnalysis(root->arg_list.arg, symbolTable);
            if(root->arg_list.arg_list != NULL) 
                semanticAnalysis(root->arg_list.arg_list, symbolTable);
            break;
        case node_arg:
            printf("IN ARG\n");
            semanticAnalysis(root->arg.expr, symbolTable);
            break;
        case node_func_def:
            printf("IN FUNC DEF\n");
            temp_identifier = root->func_def.decl->declaration.identifier;
            temp_dataType = root->func_def.decl->declaration.type->typekw.type;
            sym = lookupSymbol(symbolTable,  currentScope, temp_identifier);
            if(sym == NULL) {
                insertSymbol(symbolTable, currentScope, temp_identifier, temp_dataType, decl_func, root->lineno);
            } 
            currentScope = lookupSymbol(symbolTable, currentScope, temp_identifier);
            semanticAnalysis(root->func_def.decl, symbolTable);
            semanticAnalysis(root->func_def.params, symbolTable);
            semanticAnalysis(root->func_def.stmt_list, symbolTable);
            currentScope = NULL;
            break;
        case node_assignment:
            printf("IN ASSIGNMENT\n");
            if(root->assignment.identifier != NULL) {sym = lookupSymbol(symbolTable,  currentScope, root->assignment.identifier) ;}          
            else { semanticAnalysis(root->assignment.assignee, symbolTable); sym=lookupSymbol(symbolTable, currentScope, root->assignment.assignee->array_index.identifier); printSymbol(sym);}     
            if(sym == NULL && root->assignment.identifier != NULL) {
                semerrorno++;
                printf("Ln.%d. SEMANTIC ERROR: Undeclared variable reference : Variable %s not declared\n", root->lineno, root->assignment.identifier);
            }
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
                sym = lookupSymbol(symbolTable,  currentScope, root->factor.identifier);
                if(sym == NULL) {
                    semerrorno++;
                    printf("Ln.%d SEMANTIC ERROR: Undeclared variable reference : Variable %s not declared\n", root->lineno, root->factor.identifier);
                } else 
                {
                    if(lExprType == NULL)
                    {
                        lExprType = getSymbolTypeString(sym->dataType);
                    }
                    else if(rExprType == NULL) {
                        rExprType = getSymbolTypeString(sym->dataType);
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
        case node_array_decl:
            printf("IN ARRAY DECL\n");
            temp_dataType = root->array_decl.decl->declaration.type->typekw.type;
            temp_identifier = root->array_decl.decl->declaration.identifier;
            sym = lookupSymbol(symbolTable,  currentScope, temp_identifier);
            if(sym != NULL) {
                semerrorno++;
                if(root->lineno != NULL && temp_identifier != NULL && sym->lineno != NULL)
                {
                    printf("Ln.%d : SEMANTIC ERROR: Duplicate array declaration : Identifier %s already declared on line %d\n", root->lineno ,temp_identifier, sym->lineno);
                }    
            } else {
                if(temp_dataType != NULL && temp_identifier != NULL && root->lineno != NULL) 
                {
                    insertSymbol(symbolTable, currentScope, temp_identifier, temp_dataType, decl_var, root->lineno);
                }
            }
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

