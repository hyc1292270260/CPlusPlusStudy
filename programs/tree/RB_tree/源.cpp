#include <iostream>
#include "rb_tree.h"
int main(void)
{
	PRBT_Node root = nullptr;
	PRBT_Node node = create_node(80,'a');
	root = insert_node(root, node);
	node = create_node(90, 'b');
	root = insert_node(root, node);
	node = create_node(95, 'c');
	root = insert_node(root, node);
	node = create_node(100, 'd');
	root = insert_node(root, node);


	return 0;
}