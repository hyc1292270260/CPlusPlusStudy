#include<stdio.h>
typedef struct _Node
{
	int value;
	char name[20];
	struct _Node* next;

}Node, *pNode;
extern pNode header;
void insert_node_tail(pNode node);//插入
pNode create_node(int value, const char*name);//创建节点
void traversal_node(void);//遍历
void remove_node(int value);//删除
int back_find_node(pNode head, int k);  //查询倒数第k个
pNode reverse_node(pNode head); //逆转链表