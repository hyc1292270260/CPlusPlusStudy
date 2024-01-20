#include <iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base" << endl;
	}
	void info()
	{
		cout << "info()" << endl;
	}
	~Base()
	{
		cout << "~Base" << endl;
	}


};

void bar()
{
	Base* base = new Base;
	std::unique_ptr<Base>sp_base(base);                 //����ָ������ǰ��������һ������ֻ����һ��ָ��
	std::unique_ptr<Base>sp_base1(std::move(sp_base));
	if (sp_base1)
		sp_base1->info();
	return;
}

std::unique_ptr<Base> foo(void)
{
	std::unique_ptr<Base>sp(new Base);
	return sp;
}
int main(void)
{
	std::unique_ptr<Base>sp= foo();
	if (sp)
	{
		sp->info();
		sp.reset(nullptr);           //���ã����ö�����������������ת��
		//sp.release();               //��ǰ�ͷţ������ö�����������
	}
	return 0;
}