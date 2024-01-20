#include<stdio.h>
#include "bst_tree.h"


pNode insert_node(pNode root, pNode node)
{
	//terminal condition
	if (!root)
	{
		return node;
	}
	if (root->key < node->key)
	{
		root->right = insert_node(root->right, node);
	}
	else if (root->key > node->key)
	{
		root->left = insert_node(root->left, node);
	}
	//update
	else
	{
		root->value = node->value;
	}
	return root;
}
pNode create_node(int key, char value)
{
	pNode node = new Node();
	if (!node)
	{
		return nullptr;
	}
	if (node)
	{
		node->key = key;
		node->value = value;
		node->left = nullptr;
		node->right = nullptr;
	}
	return node;
}
pNode find_node(pNode root, int key)
{
	if (!root)
	{
		return nullptr;
	}
	if (root->key == key)
	{
		return root;
	}
	else if (root->key < key)
	{
		return find_node(root->right, key);
	}
	else if (root->key > key)
	{
		return find_node(root->left, key);
	}
	return root;

}
pNode remove_node(pNode root, int key)
{
	//ÖÕÖ¹Ìõ¼þ
	if (!root)						//no find
	{
		return nullptr;
	}
	else if (root->key == key)		//find
	{
		if (!root->left && !root->right)	
		{
			delete root;
			return nullptr;
		}
		else if ((!root->left&&root->right) || (!root->right&&root->left))
		{
			pNode node = nullptr;
			if (!root->left&&root->right)
			{
				node = root->right;
			}
			else if (!root->right&&root->left)
			{
				node = root->left;
			}
			delete root;
			root = nullptr;
			return node;
		}
		else
		{
			pNode min_node = find_min(root);
			exchange_node(root,min_node);	
			root->right = remove_node(root->right,key);
			return root;
		}	

	}
	else if (root->key < key)
	{
		root->right = remove_node(root->right,key);
	}
	else if (root->key > key)
	{
		root->right = remove_node(root->left,key);
	}
	return root;

}
pNode find_min(pNode root)
{
	pNode node = root;
	while (node->left)
	{
		node = node->left;
	}
	return node;
}
void exchange_node(pNode node1, pNode node2)
{
	int key = node1->key;
	node1->key = node2->key;
	node2->key = key;
	char value = node1->value;
	node1->value = node2->value;
	node2->value = value;
}