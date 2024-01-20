#include <iostream>
#include <string>
using namespace std;


struct Node
{
	int value;
	char name[20];
	struct Node* next;

};
class list
{
private:
	struct Node* header;

public:

	list()
	{
		Node* header = nullptr;
	}
	const char* find_node(int value)
	{
		if (!header)
			return "no";
		else
		{
			Node* temp = header;
			while (temp)
			{
				if(temp->value == value)
					return temp->name;
				else
					temp = temp->next;
			}
			return 	"no";
			
			
		}

	}

	void insert_node_tail(Node* node)
	{
		if (!node)
			return;
		if (!header)
			header = node;
		else
		{
			Node* temp = header;
			while (temp->next)
				temp = temp->next;
			temp->next = node;

		}

	}
	void insert_node_head(Node* node)
	{
		if (!node)
			return;
		if (!header)
			header = node;
		else
		{
			Node* temp = header;
			header = node;
			header->next = temp;

		}


	}
	Node* create_node(int value, const char* name)
	{
		Node* node = new Node;
		if (!node)
			return nullptr;
		node->value = value;
		node->next = nullptr;
		strcpy_s(node->name, name);
		return node;

	}
	void traversal_node(void)
	{
		if (!header)
			return;
		Node* temp = header;
		while (temp)
		{
			cout << temp->name << "  " << temp->value << endl;
			temp = temp->next;
		}

	}
	void remove_node(int value)
	{
		/*if (header->value==value)
		{
			header->next = header;
			delete header;
			header = nullptr;
		}*/
		Node* temp = header;
		Node* pre = nullptr;
		while (temp)
		{
			if (temp->value == value)
				break;
			pre = temp;
			temp = temp->next;

		}
		if (!pre)
			header = temp->next;
		else if (!temp)
			return;
		else
			pre->next = temp->next;
		delete temp;
		temp = nullptr;
		/*delete pre;
		pre = nullptr;*/

	}

	void insert_node(Node* node, int value)
	{
		if (!header)
			return ;
		else
		{
			Node* temp = header;
			Node* pre = nullptr;
			while (temp)
			{
				if (temp->value == value)
				{
					break;
				}
				else
				{
					pre = temp;
					temp = temp->next;
				}

			}
			if (!pre)
			{
				node->next = temp->next;
				header->next = node;

			}
			else if (!temp)
				return ;
			else 
			{
				node->next = temp->next;
				pre->next->next = node;
				
			}
			
			

		}
	}
};