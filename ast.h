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
    node_assignment,
    node_typekw,
    node_print_stmt,
    node_expr,
    node_term,
    node_factor,
    node_number,
} NodeType;

typedef struct Node
{
NodeType nodeType; 
union {
    struct  {struct Node* stmt_list;} program;
    struct  {struct Node* stmt; struct Node* stmt_list;} stmt_list; 
    struct  {struct Node* right;}stmt;
    struct  {struct Node* type; /* typekw node*/char* identifier;} declaration;
    struct  {char* assign; /* = */char* identifier; struct Node* expr;} assignment;
    struct  {char* operator; struct Node* left; struct Node* right;} expr;
    struct  {struct Node* expr;} print_stmt;
    struct  {char* type;} typekw;
    struct  {char* operator; struct Node* term; struct Node* factor;} term;
    struct  {struct Node* expr; struct Node* number; char* identifier;} factor;
    struct  {char* value; /*Number INT or FLOAT*/} number;
};
}Node;

Node* createNode(NodeType nodeType);
void traverseAST(Node* root, int depth, const char* direction);
void deleteAST(Node* node);
void structure(int depth, const char* direction);
const char* getNodeTypeString(NodeType type);

#endif