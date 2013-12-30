#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s Node;
struct Node_s {
  Node *left;
  Node *right;
  int value;
};

Node* create_node( int value ) {
  Node *node = malloc( sizeof( Node ) );
  node->left = NULL;
  node->right = NULL;
  node->value = value;
  return node;
}

Node* insert_node( Node *tree, int value ) {
  if( tree != NULL ) {
    if( value <= tree->value ) {
      tree->left = insert_node( tree->left, value );
    } else {
      tree->right = insert_node( tree->right, value );
    }
    return tree;
  } else {
    return create_node( value );
  }
}

void delete_tree( Node *tree ) {
  if( tree != NULL ) {
    delete_tree( tree->left );
    delete_tree( tree->right );
    free( tree );
  }
}

void print_tree( Node *tree ) {
  if( tree != NULL ) {
    print_tree( tree->left );
    print_tree( tree->right );
    printf( "%d\n", tree->value );
  }
}

size_t size_tree( Node *tree ) {
  if( tree != NULL ) {
    return size_tree( tree->left ) + 1 + size_tree( tree->right );
  } else {
    return 0;
  }
}

void apply_to_tree( Node *tree, int (*f_ptr)(int) ) {
  if( tree != NULL ) {
    apply_to_tree( tree->left, f_ptr );
    apply_to_tree( tree->right, f_ptr );
    tree->value = (*f_ptr)( tree->value );
  }
}

int sq( int x ) {
  return x * x;
}

void build_demo_tree(void) {
  Node *tree = insert_node( NULL, 0 );
  tree = insert_node( tree, 10 );
  tree = insert_node( tree, 5 );
  tree = insert_node( tree, 1 );
  tree = insert_node( tree, 11 );
  tree = insert_node( tree, 8 );
  print_tree( tree );
  printf( "Tree has %zu items.\n", size_tree( tree ) );
  apply_to_tree( tree, sq );
  print_tree( tree );
  delete_tree( tree );
}

int main(void) {
  build_demo_tree();
  return 0;
}
