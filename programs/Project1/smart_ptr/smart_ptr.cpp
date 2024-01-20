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
	std::unique_ptr<Base>sp_base(base);                 //智能指针析构前析构对象，一个对象只能有一份指针
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
		sp.reset(nullptr);           //重置，调用对象析构函数，可以转移
		//sp.release();               //提前释放，不调用对象析构函数
	}
	return 0;
}