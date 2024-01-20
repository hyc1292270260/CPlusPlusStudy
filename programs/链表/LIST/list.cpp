#include "List.h"
int main(void)
{
	struct Node* node = nullptr;
	
	
	list a;
	node = a.create_node(123, "hyc");
	//a.insert_node_tail(node);
	a.insert_node_head(node);
	node = a.create_node(456, "hhh");
	//a.insert_node_tail(node);
	a.insert_node_head(node);
	node = a.create_node(789, "pzz");
	//a.insert_node_tail(node);
	a.insert_node_head(node);
	node = a.create_node(79, "p");	
	 a.insert_node(node,456);
	a.traversal_node();
	a.remove_node(789);
	a.traversal_node();
	const char* b = new char[5];
	b = a.find_node(456);
	return 0;
}