//#include <iostream>
//
//using namespace std;
//
//template <typename InheritedT>
//class Base
//{
//public:
//	void show()
//	{
//		wcout << L"base.show()" << endl;
//	}
//	void _show()
//	{
//		static_cast<InheritedT*>(this)->show();
//	}
//
//};
//
//class Child :public Base<Child>
//{
//public:
//	void show()
//	{
//		wcout << L"child.show()" << endl;
//	}
//};
//int main(void)
//{
//  void* base;
//	Base<Child>* base = new Child();
//	base->show();
//
//	return 0;
//}