#include <iostream>
#include <functional>
using namespace std;

function<int(void)> foo(void);    //��������
int main(void)
{
	int result = foo()();        //lambda�������ã����غ���ʱջ֡���ݣ�����ֵ��ȷ��
	cout << result << endl;
	return 0;
}
//void foo(void)
//{
//	int i = 0;
//	 //goes to
//	int j = [i](void) mutable ->int      //  ()����
//	{
//		return i+1;
//	}();
//
//	cout << j << endl;
//}
function<int(void)> foo(void)
{
	int i = 0;

	function<int(void)> lambda_expe = [=](void) mutable ->int      //[=]ȫ����ֵ����&�����ò���
	{                                                              //[=,&i]����a���ã����ఴֵ
		return i+1;												   //[����ֵ](�����б�)->����ֵ{������}��
		//return i++;
	};

	return  lambda_expe;
}