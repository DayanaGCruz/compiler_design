#include "semantic.h"
#include <stdio.h>

// TO DO 
// Type matching - assignment & decl 
// sem
// var decl
// type matching 

// opt
// dead code, constatn folding, constant propogation 
// orig. 
// u = 1
// x = 1
// y = 2 + x 
// dead code
// x = 1
// y = 2 + x 
// prop
// y = 2 + 1
// folding 
// y = 3
//
#define RED "\x1B[31m"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
TAC* tacHead;
Node* temp_node;
char* temp_string;
Symbol* sym; // temp symbol pointer
char* lExprType;
char* rExprType;
Symbol* currentScope;
char* temp_dataType;
char* temp_identifier;
static Stack * operatorStack = NULL;
static Stack * operandStack = NULL;
static Stack * operandTypeStack = NULL;
int counter = 1;


void semanticAnalysis(Node* root, SymbolTable* symbolTable)
{
    if(root == NULL) return;
    sym = NULL; // Reset temp symbol
    switch (root->nodeType) 
    {
        case node_program:
            printf(RED BOLD "\nSEMANTIC ANALYSIS\n\n" RESET);
            semanticAnalysis(root->program.stmt_list, symbolTable);
             generateTACUtil(root);
             if(tacHead != NULL) {printAllTAC(tacHead);}
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
            if(sym != NULL) 
            {
                semerrorno++;
                if(root->declaration.identifier != NULL)
                {
                    printf("Ln.%d : SEMANTIC ERROR: Duplicate variable declaration : Identifier %s already declared on line %d\n", root->lineno ,root->declaration.identifier, sym->lineno);
                }    
            } else {
                printf("INSERTING SYMBOL\n");
                if(root->declaration.type->typekw.type != NULL && root->declaration.identifier != NULL) 
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
                    if(temp_identifier != NULL)
                    {
                        printf("Ln.%d : SEMANTIC ERROR: Duplicate function declaration : Identifier %s already declared on line %d\n", root->lineno ,temp_identifier, sym->lineno);
                        
                    }   
                }
            } else 
            {
                if(temp_dataType != NULL && temp_identifier != NULL) 
                {
                    insertSymbol(symbolTable, currentScope, temp_identifier, temp_dataType, decl_func, root->lineno);
                }
                currentScope = lookupSymbol(symbolTable, currentScope, temp_identifier);
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
                    if(root->param.identifier != NULL)
                    {
                        printf("Ln.%d : SEMANTIC ERROR: Duplicate parameter declaration : Identifier %s already declared on line %d\n", root->lineno ,root->param.identifier, sym->lineno);
                    }   
                } 
            } else {
                if(root->param.type->typekw.type != NULL && root->param.identifier != NULL) 
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
            semanticAnalysis(root->func_def.params, symbolTable);
            semanticAnalysis(root->func_def.stmt_list, symbolTable);
            currentScope = NULL;
            break;
        case node_assignment:
            printf("IN ASSIGNMENT\n");
            if(root->assignment.identifier != NULL) {sym = lookupSymbol(symbolTable,  currentScope, root->assignment.identifier) ;}          
            else { semanticAnalysis(root->assignment.assignee, symbolTable); sym=lookupSymbol(symbolTable, currentScope, root->assignment.assignee->array_index.identifier);}     
            if(sym == NULL && root->assignment.identifier != NULL) {
                semerrorno++;
                printf("Ln.%d. SEMANTIC ERROR: Undeclared variable reference 2 : Variable %s not declared\n", root->lineno, root->assignment.identifier);
            } else { lExprType = getSymbolTypeString(sym->dataType); }
            semanticAnalysis(root->assignment.expr, symbolTable);
            if (!checkTypeCompatibility(lExprType, rExprType)) {
            printf("Semantic error: Incompatible types in assignment\n");
            }
            break;
        case node_typekw:
            printf("IN TYPE KW\n");
            break;
        case node_array_index:
            printf("IN ARRAY INDEX\n");
            sym=lookupSymbol(symbolTable, currentScope, root->array_index.identifier);
             if(sym == NULL && root->assignment.identifier != NULL) {
                semerrorno++;
                printf("Ln.%d. SEMANTIC ERROR: Undeclared variable reference : Variable %s not declared\n", root->lineno, root->assignment.identifier);
            } else {
                if(lExprType == NULL)
                    {
                        lExprType = getSymbolTypeString(sym->dataType);
                        printf("L TYPE: %s\n", lExprType);
                    }
                    else if(rExprType == NULL) {
                        rExprType = getSymbolTypeString(sym->dataType);
                        printf("R TYPE: %s\n", rExprType);
                    }
            }
            semanticAnalysis(root->assignment.expr, symbolTable);
            break;
            break; 
        case node_print_stmt:
            printf("IN PRINT STMT\n");
            semanticAnalysis(root->print_stmt.expr, symbolTable);
            break;
        case node_expr:
            if(root->expr.left != NULL) 
            {
                semanticAnalysis(root->expr.left, symbolTable);
            }
            if (root->expr.right != NULL) {
                semanticAnalysis(root->expr.right, symbolTable);
            }
            if(root->expr.left != NULL && root->expr.right != NULL && lExprType != NULL && rExprType != NULL) { // Waiting for both expressions to be filled.
                printf("LEFT TYPE: %s\n", lExprType);
                printf("RIGHT TYPE: %s\n", rExprType);
                if(!checkTypeCompatibility(lExprType, rExprType)) {
                    semerrorno++;
                    printf("Ln.%d SEMANTIC ERROR: Type mismatch : Incompatible types %s and %s\n", root->lineno, lExprType, rExprType);
                }
                else 
                {
                    lExprType = NULL; // Reset the types
                    rExprType = NULL;
                }
            } // Assignment types
            else if(root->expr.right == NULL && lExprType != NULL && rExprType != NULL)
            {
                printf("LEFT TYPE: %s\n", lExprType);
                printf("RIGHT TYPE: %s\n", rExprType);
                if(!checkTypeCompatibility(lExprType, rExprType)) {
                    semerrorno++;
                    printf("Ln.%d SEMANTIC ERROR: Type mismatch : Incompatible types %s and %s\n", root->lineno, lExprType, rExprType);
                }
                else 
                {
                    lExprType = NULL; // Reset the types
                    rExprType = NULL;
                }
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
                        printf("L TYPE: %s\n", lExprType);
                    }
                    else if(rExprType == NULL) {
                        rExprType = getSymbolTypeString(sym->dataType);
                        printf("R TYPE: %s\n", rExprType);
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
            insertSymbol(symbolTable, currentScope, root->number.value, root->number.type, decl_const, root->lineno);
            break;
        case node_array_decl:
            printf("IN ARRAY DECL\n");
            temp_dataType = root->array_decl.decl->declaration.type->typekw.type;
            temp_identifier = root->array_decl.decl->declaration.identifier;
            sym = lookupSymbol(symbolTable,  currentScope, temp_identifier);
            if(sym != NULL) {
                semerrorno++;
                if(temp_identifier != NULL)
                {
                    printf("Ln.%d : SEMANTIC ERROR: Duplicate array declaration : Identifier %s already declared on line %d\n", root->lineno ,temp_identifier, sym->lineno);
                }    
            } else {
                if(temp_dataType != NULL && temp_identifier != NULL) 
                {
                    insertSymbol(symbolTable, currentScope, temp_identifier, temp_dataType, decl_var, root->lineno);
                }
            }
            break;
        case node_array_def:
            printf("IN ARRAY DEF\n");
            if(root->array_def.array_decl != NULL) 
                semanticAnalysis(root->array_def.array_decl, symbolTable);
            semanticAnalysis(root->array_def.expr_list, symbolTable);
            break;
        case node_expr_list:
            semanticAnalysis(root->expr_list.expr, symbolTable);
            if(root->expr_list.expr_list != NULL) 
                semanticAnalysis(root->expr_list.expr_list, symbolTable);
            break;
        default:
            printf("Unknown Node\n");
            break;
    }

}

TAC* generateTACUtil(Node* node)
{
    generateTAC(node);
    if(!isEmpty(operatorStack) && stackSize(operandStack) >= 2)
        {
        char* op = pop(operatorStack);
        char* operand2 = pop(operandStack);
        char* operand1 = pop(operandStack);
        TAC* instr = createTAC( op, operand1, operand2);
        push(operandStack, instr->label);
        printf("Instr Result: %s\n", instr->label);
        counter++;
        } else if (pop(operatorStack) == "write" && stackSize(operandStack) == 1)
        {
            char* operand = pop(operandStack);
            TAC* instr = createTAC( "write", operand, NULL);
            printf("Instr Result: %s\n", instr->label);
            counter++;
        }
    
}

TAC* generateTAC(Node* node)
{
    if (operatorStack == NULL) { operatorStack = createStack();}
    if (operandStack == NULL) { operandStack = createStack();}
    if(node != NULL) 
    {
        TAC* instr = NULL;
        switch (node->nodeType)
        {
            case node_program:
                generateTAC(node->program.stmt_list);
                /*
                while(!isEmpty(operatorStack) && stackSize(operandStack) >= 2)
                {
                    char* op = pop(operatorStack);
                    char* operand2 = pop(operandStack);
                    char* operand1 = pop(operandStack);
                    TAC* instr = createTAC( op, operand1, operand2);
                    push(operandStack, instr->label);
                    printf("Result: %s\n", instr->label);
                    counter++;
                }
                */
                break;
            case node_stmt_list:
                if(node->stmt_list.stmt != NULL)
                {
                    generateTAC(node->stmt_list.stmt);
                }
                if(node->stmt_list.stmt_list != NULL)
                {
                    generateTAC(node->stmt_list.stmt_list);
                }
                break;
            case node_stmt:
                if(node->stmt.right != NULL)
                {
                    generateTAC(node->stmt.right);
                } 
                break;
            case node_declaration:
                if(node->declaration.type != NULL)
                {
                    generateTAC(node->declaration.type);
                }
                break;
            case node_func_decl:
                if(node->func_decl.decl != NULL)
                {
                    generateTAC(node->func_decl.decl);
                }
                if(node->func_decl.params != NULL)
                {
                    generateTAC(node->func_decl.params);
                }
                break;
            case node_func_params:
                if(node->func_params.param_list != NULL)
                {
                    generateTAC(node->func_params.param_list);
                }
                break;
            case node_param_list:
                if(node->param_list.param != NULL)
                {
                    generateTAC(node->param_list.param);
                }
                if(node->param_list.param_list != NULL)
                {
                    generateTAC(node->param_list.param_list);
                }
                break;
            case node_param:
                if(node->param.type != NULL)
                {
                    generateTAC(node->param.type);
                }
                break;
            case node_func_call:
                if(node->func_call.args != NULL)
                {
                    generateTAC(node->func_call.args);
                }
                break;
            case node_func_args:
                if(node->func_args.arg_list != NULL)
                {
                    generateTAC(node->func_args.arg_list);
                }
                break;
            case node_arg_list:
                if(node->arg_list.arg != NULL)
                {
                    generateTAC(node->arg_list.arg);
                }
                if(node->arg_list.arg_list != NULL)
                {
                    generateTAC(node->arg_list.arg_list);
                }
                break;
            case node_arg:
                if(node->arg.expr != NULL)
                {
                    generateTAC(node->arg.expr);
                }
                break;
            case node_func_def:
                if(node->func_def.decl != NULL)
                {
                    generateTAC(node->func_def.decl);
                }
                if(node->func_def.params != NULL)
                {
                    generateTAC(node->func_def.params);
                }
                if(node->func_def.stmt_list != NULL)
                {
                    generateTAC(node->func_def.stmt_list);
                }
                break;
            case node_assignment:
                if(node->assignment.assignee != NULL)
                {
                    generateTAC(node->assignment.assignee);
                   
                }
                if(node->assignment.expr != NULL)
                {
                    generateTAC(node->assignment.expr);
                    createTAC("=", node->assignment.assignee->declaration.identifier, pop(operandStack));
                    //
                }
                break;
            case node_typekw:
                break;
            case node_array_index:
                if(node->array_index.identifier != NULL)
                {
                    //generateTAC(node->array_index.identifier);
                }
                break;
            case node_print_stmt:
                if(node->print_stmt.expr != NULL)
                {
                    generateTAC(node->print_stmt.expr);
                }
                push(operatorStack, "write");
                printf("At print stmt\n");
                break;
            case node_expr_list:
                if(node->expr_list.expr != NULL)
                {
                    generateTAC(node->expr_list.expr);
                }
                if(node->expr_list.expr_list != NULL)
                {
                    generateTAC(node->expr_list.expr_list);
                }
                break;
            case node_expr:
            
               printf("IN EXPR\n");
               
               if (node->expr.operator != NULL)
                {
                    printf("Operator: %s\n", node->expr.operator);
                    push(operatorStack, node->expr.operator);
                }
                
                                 
                if(node->expr.left != NULL)
                {
                    generateTAC(node->expr.left);
                }

                
                if(node->expr.right != NULL)
                {
                    generateTAC(node->expr.right);
                }

                if(!isEmpty(operatorStack) && stackSize(operandStack) >= 2)
                {
                    char* op = pop(operatorStack);
                    char* operand2 = pop(operandStack);
                    char* operand1 = pop(operandStack);
                    TAC* instr = createTAC( op, operand1, operand2);
                    push(operandStack, instr->label);
                    printf(" Instr Result: %s\n", instr->label);
                    counter++;
                }
                
                
                break;
            case node_term:
                
                if (node->term.operator != NULL)
                {
                    push(operatorStack, node->term.operator);
                    printf("Operator: %s\n", node->term.operator);
                }
                generateTAC(node->term.factor);
                generateTAC(node->term.term);

                  if(!isEmpty(operatorStack) && stackSize(operandStack) >= 2 )
                {
                    char* op = pop(operatorStack);
                    char* operand1 = pop(operandStack);
                    char* operand2 = pop(operandStack);
                    TAC* instr = createTAC( op, operand1, operand2);
                    push(operandStack, instr->label);
                    printf(" Instr Result: %s\n", instr->label);
                    counter++;
                }
                
                break;
            case node_factor:
                generateTAC(node->factor.number);
                generateTAC(node->factor.expr);
                break;
            case node_number:
                printf("TAC Value: %s\n", node->number.value);
                push(operandStack, node->number.value);
                TAC* instr = createTAC("=", pop(operandStack) , NULL);
                push(operandStack, instr->label);
                printf(" Instr Result: %s\n", instr->label);
                counter++;
                break;
            default:
                printf("Unrecognized node in TAC Generation\n");
                break;
        }    
    }
}

int checkTypeCompatibility(const char* type1, const char* type2)
{
    printf("CHECKING TYPE COMPATIBILITY\n");
    if (type1 == NULL || type2 == NULL)
    {
        printf("%s", "Type is NULL\n");
        return 0;
    }
    printf("TYPE 1: %s, TYPE 2: %s\n", type1, type2);
    if (strcmp(type1, type2) == 1) { return 1;} 
    else {return 0;} 
}

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);  // Exit if memory allocation fails
    }
    stack->top = -1;
    return stack;
}

void push (Stack* stack, char* value)
{
    if (stack->top < 99)
    {
        stack->data[++stack->top] = value;
    }
}

char* pop(Stack* stack) {
    
    if (stack->top >= 0) { 
        char* value = stack->data[stack->top];  // Retrieve the top element
        stack->data[stack->top] = NULL;          // Clear the reference
        stack->top--;                            // Move the top pointer down
        return value;
    }
    return NULL;  // Return NULL if the stack is empty
}


int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

int stackSize(Stack* stack) {
    return stack->top + 1;  // top is -1 when empty, so adding 1 gives the count
}

TAC* createTAC( char* op, char* arg1, char* arg2) {
    char buffer[30];
    TAC* instr = (TAC*)malloc(sizeof(TAC));
    if (!instr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);  // Exit if memory allocation fails
    }

    instr->op = op;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    sprintf(buffer, "T%d", counter);
    instr->label = strdup(buffer);
    instr->next = NULL;

    // Insert at head if tacHead is NULL
    if (tacHead == NULL) {
        tacHead = instr;
    } else {
        // Append to the end of the list
        TAC* temp = tacHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = instr;
    }
    
    return instr;
}


void printTAC(TAC* tac)
{
    printf(" = %s %s %s\n", tac->op, tac->arg1, tac->arg2);
}

// TODO 
// Support write statements in TAC
// Resolve TAC to load constants into reg. before use 
// t0 = 1
// t1 = 2
// t3 = t0 + t1

void printAllTAC(TAC* head) {
    TAC* current = head;
    while (current != NULL) {
        if (current->arg2 == NULL)
    {
        printf("%s -> %s %s\n", current->label, current->op, current->arg1);
    } else {
        printf(
            "%s -> %s %s %s\n", 
            current->label,
            current->arg1, 
            current->op, 
            current->arg2
            );
    }
        current = current->next;
    }
}
