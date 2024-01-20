#include<stdio.h>
#include"linked_list.h"
#include<stdlib.h>
#include<string.h>
pNode header = NULL;
void insert_node_tail(pNode node)
{
	if (!node)
		return;
	if (!header)         // Ã»ÓĞÍ·
		header = node;
	else
	{
		pNode temp = header;
		while (temp->next)
			temp = temp->next;
		temp->next = node;

	}

}
pNode create_node(int value, const char* name)
{
	pNode node = (pNode)malloc(sizeof(node));
	if (!node)
		return NULL;
	node->value = value;
	node->next = NULL;
	strcpy(node->name, name);
	return node;

}
void traversal_node(void)
{
	pNode temp = header;
	if (!header)
		return;
	while (temp)
	{
		printf("%s,%i\n", temp->name, temp->value);
		temp = temp->next;

	}

}
void remove_node(int value)
{
	pNode temp = header,
		previous = NULL;
	while (temp)
	{
		if (temp->value == value)
			break;
		previous = temp;
		temp = temp->next;
	}
	if (!temp)
		return;
	else if (!previous)
		header = temp->next;
	else
		previous->next = temp->next;


	//free(temp);
	//temp = NULL;
}

int back_find_node(pNode head, int k)
{
	if (!head)
		return -1;
	else
	{
		pNode temp = head, after = head;
		int count = 0;
		while (temp->next)
		{
			++count;
			if (count >= k)
				after = after->next;			
			temp = temp->next;
		}
		if (count < k)
			return -1;
		else
			printf("%s,%i\n", after->name, after->value);
		return 0;
	}

}
pNode reverse_node(pNode head)
{
	if (!head || !(head->next))
		return head;
	pNode rhead = NULL;
	while (head)
	{
		pNode temp = head;
		head = temp->next;
		temp->next = rhead;
		rhead = temp;
	}
	return rhead;
	
}