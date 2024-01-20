#pragma once
#include <iostream>

enum class Color 
{
	black,
	red

};
typedef struct _RBT_Node
{
	Color color;
	int key;
	char value;
	struct _RBT_Node *left;
	struct _RBT_Node *right;

}RBT_Node,*PRBT_Node;
void exchange_color(PRBT_Node a, PRBT_Node b);
void flip_color(PRBT_Node root);
PRBT_Node left_rotate(PRBT_Node root);
PRBT_Node right_rotate(PRBT_Node root);
PRBT_Node insert_rb_node(PRBT_Node root, PRBT_Node node);
bool is_red(PRBT_Node node);
PRBT_Node create_node(int key, char value);
PRBT_Node insert_node(PRBT_Node root, PRBT_Node node);