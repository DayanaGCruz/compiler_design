#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void structure(int depth, const char* direction) 
{
    /* Print indentation for structure based on tree depth */
    for (int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("%s ", direction);
}

/* Helper function to convert enum NodeType to a string for printing */
const char* getNodeTypeString(NodeType type) {
    switch (type) {
        case node_program: return "Program";
        case node_stmt_list: return "Statement List";
        case node_stmt: return "Statement";
        case node_declaration: return "Declaration";
        case node_assignment: return "Assignment";
        case node_typekw: return "Type";
        case node_print_stmt: return "Print Statement";
        case node_expr: return "Expression";
        case node_term: return "Term";
        case node_factor: return "Factor";
        case node_number: return "Number";
        default: return "unknown";
    }
}

/* Create a new node based on the passed node type */
Node* createNode(NodeType nodeType) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->nodeType = nodeType;  // Set node type

    /* Initialize the attributes for each node type */
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
        case node_assignment:
            node->assignment.assign = NULL;
            node->assignment.identifier = NULL;
            node->assignment.expr = NULL;
            break;
        case node_typekw:
            node->typekw.type = NULL;
            break;
        case node_print_stmt:
            node->print_stmt.expr = NULL;
            break;
        case node_expr:
            node->expr.operator = '\0'; /* Initialize operator*/
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
            break;
        default:
            printf("AST | Unrecognizable NodeType argument passed\n");
            break;
    }
    return node;
}

/* Recursive function to print the AST (pre-order traversal) */
void traverseAST(Node* root, int depth, const char* direction) {
    if (root == NULL) return;

    /* Recursively print the left and right children */
    structure(depth, direction);
    
    switch (root->nodeType) {
        case node_program:
            printf("\n|| ABSTRACT SYNTAX TREE (AST) <~> PARSE TREE ||\n\n");
            printf("%s\n", getNodeTypeString(root->nodeType));
            traverseAST(root->program.stmt_list, depth + 1, "↘");
            break;
        case node_stmt_list:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->stmt_list.stmt != NULL) 
                traverseAST(root->stmt_list.stmt, depth + 1, "↙");
            if(root->stmt_list.stmt_list != NULL) 
                traverseAST(root->stmt_list.stmt_list, depth + 1, "↘");
            break;
        case node_stmt:
            printf("%s\n", getNodeTypeString(root->nodeType));
            if(root->stmt.right != NULL)
                traverseAST(root->stmt.right, depth + 1, "↘");
            break;
        case node_declaration:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth + 1, "|");
            printf("Identifier: %s\n", root->declaration.identifier);
            traverseAST(root->declaration.type, depth + 1, "↘");
            break;
        case node_assignment:
            printf("%s\n", getNodeTypeString(root->nodeType));
            structure(depth+1, "|");
            printf("Assign: %s\n", root->assignment.assign);
            structure(depth+1, "|");
            printf("Identifier: %s\n", root->assignment.identifier);
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
                traverseAST(root->expr.left, depth + 1, "↙");
            if (root->expr.right != NULL) 
                traverseAST(root->expr.right, depth + 1, "↘");
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
        default:
            printf("Unknown Node\n");
            break;
    }
}


/* Delete the AST recursively */
/* Delete the AST recursively */
void deleteAST(Node* node) {
    if (node == NULL) return;
    /* Free dynamically allocated fields inside the node */
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
        default:
            break;
    }

    /* Free the node itself */
    free(node);
}
