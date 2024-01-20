#include<stdio.h>
#include "bst_tree.h"

int main(void)
{
	pNode node = create_node(14, 'a');
	pNode root = insert_node(nullptr, node);
	node = create_node(18, 'b');
	root = insert_node(root, node);
	node = create_node(16, 'c');
	root = insert_node(root, node);
	node = create_node(10, 'd');
	root = insert_node(root, node);
	root = remove_node(root,18);

	if (node = find_node(root, 18))
		printf("%c\n", node->value);	
	else
		printf("no found");
	
		
	return 0;
}