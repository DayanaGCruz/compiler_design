#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    node_program,
    node_stmt_list,
    node_stmt,
    node_declaration,
    node_func_decl,
    node_array_decl,
    node_array_index, 
    node_array_def,
    node_func_call,
    node_func_def,
    node_func_args,
    node_arg_list,
    node_arg,
    node_func_params,
    node_param_list,
    node_param,
    node_assignment,
    node_typekw,
    node_print_stmt,
    node_expr,
    node_term,
    node_factor,
    node_number,
    node_return_stmt,
    node_expr_list,
} NodeType;

typedef struct Node
{
NodeType nodeType; 
int lineno;
union {
    // TO DO - MAKE IDENTFIER ITS OWN NODE TYPE
    struct  {struct Node* stmt_list;} program;
    struct  {struct Node* stmt; struct Node* stmt_list;} stmt_list; 
    struct  {struct Node* right;} stmt;
                    // typekew node 
    struct  {struct Node* type; char* identifier;} declaration;
                    // Return type - typekw node        // func_params node 
    struct  {struct Node* decl; struct Node* params;} func_decl;
    struct  {struct Node* param_list;} func_params;
    struct  {struct Node* param; struct Node* param_list;} param_list;
                    // typekw node 
    struct  {struct Node* type; char* identifier;} param;
    struct  {char* identifier; struct Node* args;} func_call;
    struct  {struct Node* arg_list;} func_args;
    struct  {struct Node* arg; struct Node* arg_list;} arg_list;
    // An expression can be processed to a term, factor, or identifier according to the grammar
    struct  {struct Node* expr;} arg;
    struct {struct Node* decl; struct Node* params; struct Node* stmt_list;} func_def;
    struct  {char* assign; /* = */char* identifier; struct Node* assignee; struct Node* expr;} assignment;
    struct  {char* operator; struct Node* left; struct Node* right;} expr;
    struct  {struct Node* expr;} print_stmt;
    struct  {char* type;} typekw;
    struct  {char* operator; struct Node* term; struct Node* factor;} term;
    struct  {struct Node* expr; struct Node* number; char* identifier;} factor;
            // int or float 
    // FIXME - change value type to kw from? 
    struct  {char* type; char* value; } number;
    struct {struct Node* decl; struct Node* size; } array_decl;
    struct { union {struct Node* array_decl; char* identifier; }; struct Node* expr_list;} array_def;
    struct {struct Node* expr; struct Node* expr_list; } expr_list;
    struct {struct Node* type; char* identifier; struct Node* index; } array_index;
    struct {struct Node* expr;} return_stmt;
};
}Node;

Node* createNode(NodeType nodeType);
void traverseAST(Node* root, int depth, const char* direction);
void deleteAST(Node* node);
void structure(int depth, const char* direction);
const char* getNodeTypeString(NodeType type);

#endif