#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#define RED "\x1B[31m"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
void structure(int depth, const char* direction) 
{
    // Print indentation for structure based on tree depth
    for (int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("%s ", direction);
}

// Helper function to convert enum NodeType to a string for printing
const char* getNodeTypeString(NodeType type) {
    switch (type) {
        case node_program: return "Program";
        case node_stmt_list: return "Statement List";
        case node_stmt: return "Statement";
        case node_declaration: return "Declaration";
        case node_func_decl: return "Function Declaration";
        case node_assignment: return "Assignment";
        case node_typekw: return "Type";
        case node_func_args: return "Arguments";
        case node_arg_list: return "Argument List";
        case node_arg: return "Argument";
        case node_func_params: return "Parameters";
        case node_param_list: return "Param List";
        case node_param: return "Param";
        case node_func_def: return "Function Definition";
        case node_func_call: return "Function Call";
        case node_array_decl: return "Array Declaration";
        case node_array_index: return "Array Index";
        case node_print_stmt: return "Print Statement";
        case node_expr: return "Expression";
        case node_term: return "Term";
        case node_factor: return "Factor";
        case node_number: return "Number";
        case node_array_def: return "Array Definition";
        case node_expr_list: return "Expression List";
        case node_return_stmt: return "Return Statement";
        default: return "unknown";
    }
}

// Create a new node based on the passed node type
Node* createNode(NodeType nodeType) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->nodeType = nodeType;  // Set node type
    int lineno = 0;
    // Initialize the attributes for each node type 
    switch (nodeType) {
        case node_program:
            node->program.stmt_list = NULL;
            break;
        case node_stmt_list:
            node->stmt_list.stmt = NULL;
            node->stmt_list.stmt_list = NULL;
            break;
        case node_stmt:
            node->stmt.right = NULL;
            break;
        case node_declaration:
            node->declaration.type = NULL;
            node->declaration.identifier = NULL;
            break;
        case node_func_call:
            node->func_call.identifier = NULL;
            node->func_call.args = NULL;
            break;
        case node_func_decl:
            node->func_decl.decl = NULL;
            node->func_decl.params = NULL;
            break;
        case node_func_params:
            node->func_params.param_list = NULL;
            break;
        case node_func_args:
            node->func_args.arg_list = NULL;
            break;
        case node_arg_list:
            node->arg_list.arg = NULL;
            node->arg_list.arg_list = NULL;
            break;
        case node_arg:
            node->arg.expr = NULL;
            break;
        case node_param_list:
            node->param_list.param = NULL; 
            node->param_list.param_list = NULL;
            break;
        case node_param: 
            node->param.type = NULL;
            node->param.identifier = NULL;
            break;
        case node_func_def:
            node->func_def.decl = NULL;
            node->func_def.params = NULL;
            node->func_def.stmt_list = NULL;
            break;
        case node_assignment:
            node->assignment.assign = NULL;
            node->assignment.identifier = NULL;
            node->assignment.expr = NULL;
            node->assignment.assignee = NULL;
            break;
        case node_typekw:
            node->typekw.type = NULL;
            break;
        case node_print_stmt:
            node->print_stmt.expr = NULL;
            break;
        case node_expr:
            node->expr.operator = NULL; 
            node->expr.left = NULL;
            node->expr.right = NULL;
            break;
        case node_term:
            node->term.operator = NULL;
            node->term.term = NULL;
            node->term.factor = NULL;
            break;
        case node_factor:
            node->factor.expr = NULL;
            node->factor.number = NULL;
            node->factor.identifier = NULL;
            break;
        case node_number:
            node->number.value = NULL;
            node->number.type = NULL;
            break;
        case node_array_decl:
            node->array_decl.decl = NULL;
            node->array_decl.size = NULL;
            break;
        case node_array_def:
            node->array_def.array_decl = NULL;
            node->array_def.identifier = NULL;
            node->array_def.expr_list = NULL;
            break;
        case node_expr_list:
            node->expr_list.expr = NULL;
            node->expr_list.expr_list = NULL;
            break;
        case node_array_index:
            node->array_index.identifier = NULL;
            node->array_index.index = NULL;
            break;
        case node_return_stmt:
            node->return_stmt.expr = NULL;
            break;
        default:
            printf("AST | Unrecognizable NodeType argument passed\n");
            break;
    }
    return node;
}

// Recursive function to print the AST (pre-order traversal)
void traverseAST(Node* root, int depth, const char* direction) {
    if (root == NULL) return;

    // Recursively print the left and right children
    structure(depth, direction);
    
    switch (root->nodeType) {
        case node_program:
            printf(RED BOLD "\nABSTRACT SYNTAX TREE (AST) <~> PARSE TREE\n\n" RESET);
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->program.stmt_list, depth + 1, "↘");
            break;
        case node_stmt_list:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->stmt_list.stmt != NULL) 
                traverseAST(root->stmt_list.stmt, depth + 1, "↙");
            if(root->stmt_list.stmt_list != NULL) 
                traverseAST(root->stmt_list.stmt_list, depth + 1, "↘");
            else structure(depth + 1, "| Empty\n");
            break;
        case node_stmt:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->stmt.right != NULL)
                traverseAST(root->stmt.right, depth + 1, "↘");
            break;
        case node_declaration:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth + 1, "|");
            if(root->declaration.identifier != NULL) printf("Identifier: %s\n", root->declaration.identifier);
            traverseAST(root->declaration.type, depth + 1, "↘");
            break;
        case node_func_decl:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->func_decl.decl, depth + 1, "↙");
            traverseAST(root->func_decl.params, depth + 1, "↘");
            break;
        case node_func_params:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->func_params.param_list != NULL) 
                traverseAST(root->func_params.param_list, depth + 1, "↘");
            break;
        case node_param_list:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->param_list.param, depth + 1, "↙");  // Parameter list will always have a parameter 
            if(root->param_list.param_list != NULL) // Parameter list may be 1 or more
                traverseAST(root->param_list.param_list, depth + 1, "↘");
            break;
        case node_param: 
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth+1, "|");
            printf("Identifier: %s\n", root->param.identifier);
            traverseAST(root->param.type, depth + 1, "↘");
            break;
        case node_func_call:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth + 1, "|");
            printf("Identifier: %s\n", root->func_call.identifier);
            traverseAST(root->func_call.args, depth + 1, "↘");
            break;
        case node_func_args:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->func_args.arg_list != NULL) // Function arguments may be empty with 0 parameters (no parameter list) 
                traverseAST(root->func_args.arg_list, depth + 1, "↘");
            else structure(depth + 1, "| Empty\n");
            break;
        case node_arg_list:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->arg_list.arg, depth + 1, "↙");
            if(root->arg_list.arg_list != NULL) 
                traverseAST(root->arg_list.arg_list, depth + 1, "↘");
            break;
        case node_arg:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->arg.expr, depth + 1, "↙");
            break;
        case node_func_def:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->func_def.decl, depth + 1, "↙");
            traverseAST(root->func_def.params, depth + 1, "↙");
            traverseAST(root->func_def.stmt_list, depth + 1, "↘");
            break;
        case node_assignment:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth+1, "|");
            printf("Assign: %s\n", root->assignment.assign);
            if (root->assignment.identifier != NULL) 
            {
                structure(depth+1, "|");
                printf("Identifier: %s\n", root->assignment.identifier);
            }
            else traverseAST(root->assignment.assignee, depth + 1, "↙");
            traverseAST(root->assignment.expr, depth + 1, "↘");
            break;
        case node_typekw:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth+1, "|");
            printf("%s\n", root->typekw.type);
            break;
        case node_print_stmt:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->print_stmt.expr, depth + 1, "");
            break;
        case node_expr:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->expr.operator != NULL) {
                structure(depth + 1, "|");
                printf("Operator: %s\n", root->expr.operator);
            }
            if(root->expr.left != NULL)
            {
                traverseAST(root->expr.left, depth + 1, "↙");
            }
            else structure(depth + 1, "| L Empty \n");
            if (root->expr.right != NULL) 
            {
                traverseAST(root->expr.right, depth + 1, "↘");
            }
            else structure(depth + 1, "| R Empty \n");
            break;
        case node_term:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if (root->term.operator != NULL) 
            {
                structure(depth + 1, "|");
                printf("Operator: %s\n", root->term.operator);
            } 
            if (root->term.factor != NULL)
                traverseAST(root->term.factor, depth + 1, "↙");
            if (root->term.term != NULL)
                traverseAST(root->term.term, depth + 1, "↘");
            break;
        case node_factor:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if (root->factor.identifier != NULL) {
                structure(depth + 1, "|");
                printf("Identifier: %s\n", root->factor.identifier);
            }
            if (root->factor.expr != NULL)
                traverseAST(root->factor.expr, depth + 1, "↙");
            if (root->factor.number != NULL)
                traverseAST(root->factor.number, depth + 1, "↘");
            break;
        case node_number:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth + 1, "|");
            printf("Value: %s\n", root->number.value);
            break;
        case node_expr_list:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->expr_list.expr, depth + 1, "↙");
            if (root->expr_list.expr_list != NULL)
                traverseAST(root->expr_list.expr_list, depth + 1, "↘");
            break;
        case node_array_decl:
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->array_decl.decl, depth + 1, "↙");
            structure(depth + 1, "| Size: \n");
            traverseAST(root->array_decl.size, depth + 1, "↘");
            break;
        case node_array_def:   
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->array_def.expr_list, depth + 1, "↘");
            break;
        case node_array_index:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth + 1, "|");
            printf("Array Identifier: %s\n", root->array_index.identifier);
            structure(depth + 1, "| Index: \n");
            traverseAST(root->array_index.index, depth + 1, "↘");
            break;
        case node_return_stmt:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth + 1, "| Return Value: \n");
            traverseAST(root->return_stmt.expr, depth + 1, "↘");
            break;
        default:
            printf("Unknown Node\n");
            break;
    }
}

// Delete the AST recursively
void deleteAST(Node* node) {
    if (node == NULL) return;
    // Free dynamically allocated fields inside the node
    switch (node->nodeType) {
        case node_program:
            deleteAST(node->program.stmt_list);
            break;
        case node_stmt_list:
            deleteAST(node->stmt_list.stmt);
            deleteAST(node->stmt_list.stmt_list);
            break;
        case node_stmt:
            deleteAST(node->stmt.right);
            break;
        case node_declaration:
            if (node->declaration.type) free(node->declaration.type);
            if (node->declaration.identifier) free(node->declaration.identifier);
            break;
        case node_assignment:
            if (node->assignment.assign) free(node->assignment.assign);
            if (node->assignment.identifier) free(node->assignment.identifier);
            deleteAST(node->assignment.assignee);
            deleteAST(node->assignment.expr);
            break;
        case node_typekw:
            if (node->typekw.type) free(node->typekw.type);
            break;
        case node_print_stmt:
            deleteAST(node->print_stmt.expr);
            break;
        case node_expr:
            deleteAST(node->expr.left);
            deleteAST(node->expr.right);
            break;
        case node_number:
            if (node->number.value) free(node->number.value);
            break;
        case node_term:
            if (node->term.operator) free(node->term.operator);
            deleteAST(node->term.term);
            deleteAST(node->term.factor);
            break;
        case node_factor:
            if (node->factor.identifier) free(node->factor.identifier);
            deleteAST(node->factor.expr);
            deleteAST(node->factor.number);
            break;
        case node_func_decl:
            deleteAST(node->func_decl.decl);
            deleteAST(node->func_decl.params);
            break;
        case node_func_params:
            deleteAST(node->func_params.param_list);
            break;
        case node_param_list:
            deleteAST(node->param_list.param);
            deleteAST(node->param_list.param_list);
            break;
        case node_param:
            deleteAST(node->param.type);
            if (node->param.identifier) free(node->param.identifier);
            break;
        case node_func_call:
            if (node->func_call.identifier) free(node->func_call.identifier);
            deleteAST(node->func_call.args);
            break;
        case node_func_args:
            deleteAST(node->func_args.arg_list);
            break;
        case node_arg_list:
            deleteAST(node->arg_list.arg);
            deleteAST(node->arg_list.arg_list);
            break;
        case node_arg:
            deleteAST(node->arg.expr);
            break;
        case node_func_def:
            deleteAST(node->func_def.decl);
            deleteAST(node->func_def.params);
            deleteAST(node->func_def.stmt_list);
            break;
        case node_array_decl:
            deleteAST(node->array_decl.decl);
            deleteAST(node->array_decl.size);
            break;
        case node_array_def:
            deleteAST(node->array_def.expr_list);
            break;
        case node_return_stmt:
            deleteAST(node->return_stmt.expr);
            break;
        default:
            break;
    }

    // Free the node itself
    free(node);
}
