#include"linked_list.h"
int main(void)
{
	pNode node = create_node(1,"hyc");
	insert_node_tail(node);
	node = create_node(5, "hhh");
	insert_node_tail(node);
	node = create_node(7, "pz");
	insert_node_tail(node);
	node = create_node(78, "z");
	insert_node_tail(node);
	node = create_node(39, "p");
	insert_node_tail(node);
	traversal_node();
	//remove_node(78);
	//traversal_node();
	
	int b = back_find_node(header, 4);
	header = reverse_node(header);
	traversal_node();

	return 0;
}