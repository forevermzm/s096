#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
  struct Node_s *left;
  struct Node_s *right;
  int value;
} Node;

Node* create_node( int value ) {
  Node *node = malloc( sizeof( Node ) );
  node->left = NULL;
  node->right = NULL;
  node->value = value;
  return node;
}

void delete_tree( Node *tree ) {
  // fill out
}

Node* insert_node( Node *tree, int value ) {
  // delete
}

size_t size_tree( Node *tree ) {
  // fill out
}

int main(void) {

  return 0;
}
