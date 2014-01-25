#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

void build_demo_tree(void) {
  Node *tree = insert_node( NULL, -1 );
  tree = insert_node( tree, 10 );
  tree = insert_node( tree, 5 );
  tree = insert_node( tree, 1 );
  tree = insert_node( tree, 11 );
  tree = insert_node( tree, 8 );
  print_tree( tree );
  printf( "Tree has %zu items.\n", size_tree( tree ) );
  int treemult = 1;
  reduce_tree( tree, mult, &treemult );
  printf( "Treemult = %d\n", treemult );
  delete_tree( tree );
}

int main(void) {
  build_demo_tree();
  return 0;
}
