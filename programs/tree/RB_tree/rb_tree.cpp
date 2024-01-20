#include "rb_tree.h"


void exchange_color(PRBT_Node a, PRBT_Node b)
{
	PRBT_Node temp = new RBT_Node();
	temp->color = a->color;
	a->color = b->color;
	b->color = temp->color;

}
void flip_color(PRBT_Node root)
{
	if (!root)
	{
		return;
	}
	root->color = Color::red;
	if (root->left)
	{
		root->left->color = Color::black;
	}
	if (root->right)
	{
		root->right->color = Color::black;
	}

}

PRBT_Node left_rotate(PRBT_Node root)
{
	PRBT_Node node;
	node = root->right;
	root->right = node->left;
	node->left = root;
	exchange_color(node, root);
	return node;
}
PRBT_Node right_rotate(PRBT_Node root)
{
	PRBT_Node node;
	node = root->left;
	root->left = node->right;
	node->right = root;
	return node;
}
bool is_red(PRBT_Node node)
{
	if (!node)
	{
		return false;
	}
	else
		return node->color == Color::red ? true : false;
}
PRBT_Node insert_rb_node(PRBT_Node root, PRBT_Node node)
{
	//terminal condition & down
	if (!root)
	{
		return node;
	}
	if (root->key == node->key)
	{
		//update
		root->value = node->value;
		return root;
	}
	//2-3-4 树递归下降时不能用4型节点
	if (is_red(root->left) && is_red(root->right))
	{
		flip_color(root);
	}
	if (node->key < root->key)
	{
		root->left = insert_rb_node(root->left, node);
	}
	else
	{
		root->right = insert_rb_node(root->right, node);
	}

	//up & dynamic adjust
	if (is_red(root->right) && !is_red(root->left))
	{
		root = left_rotate(root);
	}
	if (is_red(root->left) && is_red(root->left->left))
	{
		root = right_rotate(root);
	}
	//2-3 tree 不允许有4节点
	/*if (is_red(root->left) && is_red(root->right))
	{
		flip_color(root);
	}*/
	return root;
}
PRBT_Node create_node(int key, char value)
{
	PRBT_Node node = new RBT_Node();
	node->color = Color::red;
	node->key = key;
	node->value = value;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

PRBT_Node insert_node(PRBT_Node root, PRBT_Node node)
{
	//ensure the root's color is black
	root = insert_rb_node(root, node);
	root->color = Color::black;
	return root;
}
