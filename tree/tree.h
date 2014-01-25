#ifndef _TREE_H
#define _TREE_H

typedef struct Node_s Node;

typedef struct Tree_s {
  Node *root;
} Tree;

Tree* insert_node( Node *tree, int value );
void delete_tree( Tree *tree );
void print_tree( Tree *tree );
size_t size_tree( Tree *tree );

#endif // _TREE_H
