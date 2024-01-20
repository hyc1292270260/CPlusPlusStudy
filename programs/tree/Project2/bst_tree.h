#pragma once
typedef struct  _Node
{
	int key;
	char value;
	struct _Node* left;
	struct _Node* right;

}Node, *pNode;
pNode insert_node(pNode root, pNode node);
pNode create_node(int key, char value);
pNode find_node(pNode root, int key);
pNode remove_node(pNode root, int key);
void exchange_node(pNode node1, pNode node2);
pNode find_min(pNode root);