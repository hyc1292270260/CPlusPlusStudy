#include<iostream>
#include<vector>
#include<algorithm>      //算法库 
using namespace std;
int main(void)
{
	vector<int>vec;     //向量，动态数组
	for (int i = 0; i < 10; ++i)
	{
		cout << "before push" << i+1 << " is " << vec.capacity() << "";
		vec.push_back(i + 1);
		cout << "after push" << i+1 << " is " <<  vec.capacity() << endl;
	}
		
	vector<int>::iterator it;   //vector内部类迭代器对象it
	
	it = find(vec.begin(), vec.end(), 6);  //算法库查找算法
	if (it != vec.end())
		*it = 20;
		


	for (it = vec.begin(); it != vec.end(); )
	{
		if (*it == 7)

			it = vec.erase(it);

		else
			++it;
	}
	/*for (it = vec.begin(); it != vec.end(); ++it)//左闭右开
		cout << *it << endl;*/
	//vector<int>::reverse_iterator rit;                  //逆迭代器
	// for (rit = vec.rbegin(); rit != vec.rend(); ++rit)
	//	cout << *rit << endl;
	for (auto it: vec)                          //范围循环
	{
		cout << it << endl;
	}
 	return 0;
	
}
//  emplace_back();