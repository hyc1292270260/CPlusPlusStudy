#include<stdio.h>
typedef struct _Node
{
	int value;
	char name[20];
	struct _Node* next;

}Node, *pNode;
extern pNode header;
void insert_node_tail(pNode node);//����
pNode create_node(int value, const char*name);//�����ڵ�
void traversal_node(void);//����
void remove_node(int value);//ɾ��
int back_find_node(pNode head, int k);  //��ѯ������k��
pNode reverse_node(pNode head); //��ת����