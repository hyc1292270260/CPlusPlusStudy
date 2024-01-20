#include <iostream>
#include <functional>
using namespace std;

function<int(void)> foo(void);    //函数类型
int main(void)
{
	int result = foo()();        //lambda捕获引用，返回函数时栈帧塌陷，返回值不确定
	cout << result << endl;
	return 0;
}
//void foo(void)
//{
//	int i = 0;
//	 //goes to
//	int j = [i](void) mutable ->int      //  ()调用
//	{
//		return i+1;
//	}();
//
//	cout << j << endl;
//}
function<int(void)> foo(void)
{
	int i = 0;

	function<int(void)> lambda_expe = [=](void) mutable ->int      //[=]全部按值捕获，&按引用捕获
	{                                                              //[=,&i]除了a引用，其余按值
		return i+1;												   //[捕获值](参数列表)->返回值{函数体}；
		//return i++;
	};

	return  lambda_expe;
}