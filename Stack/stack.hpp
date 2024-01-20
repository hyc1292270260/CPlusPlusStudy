struct StackNode
{
	StackNode* pre;
	void* data;
};

class Stack
{
public:
	template<class T>
	void push(const T& value);

	template<class T>
	void pop(T& value);

private:
	StackNode* top = nullptr;
};

template<class T>
void Stack::push(const T& value)
{
	StackNode* temp = new StackNode();
	temp->data = new T(value);
	if (top)
	{
		temp->pre = top;
	}
	top = temp;
}

template<class T>
void Stack::pop(T& value)
{
	if (!top) return;

	StackNode* temp = top;
	top = top->pre;
	value = *(static_cast<T*>(temp->data));
	delete temp->data;
	delete temp;
}
