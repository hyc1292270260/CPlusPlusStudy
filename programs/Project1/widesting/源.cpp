#include<iostream>
#include<wchar.h>   
using namespace std;
int main(void)
{
	char str[10] = "Hello";
	wchar_t str1[10] = L"Hello";   //宽字符集
	wchar_t str2[10] = LR"(Hell\no)";  //原始字符集
	//cout << strlen(str) << " " << wcslen(str1)<<"\n" <<endl;
	//cout << sizeof(str) << " " << sizeof(str1) << endl;
	cout << str2 << endl;
 	return 0;

}
//int main(int ac, char* av[])   //argument count,argument value
//{
//	for (int i = 0; i < ac; ++i)   //int wmain(int ac, wchar_t* av[])
//	{
//		cout << av[i] << endl;
//	}
//	return 0;
//
//}