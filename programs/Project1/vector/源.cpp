#include<iostream>
#include<vector>
#include<algorithm>      //�㷨�� 
using namespace std;
int main(void)
{
	vector<int>vec;     //��������̬����
	for (int i = 0; i < 10; ++i)
	{
		cout << "before push" << i+1 << " is " << vec.capacity() << "";
		vec.push_back(i + 1);
		cout << "after push" << i+1 << " is " <<  vec.capacity() << endl;
	}
		
	vector<int>::iterator it;   //vector�ڲ������������it
	
	it = find(vec.begin(), vec.end(), 6);  //�㷨������㷨
	if (it != vec.end())
		*it = 20;
		


	for (it = vec.begin(); it != vec.end(); )
	{
		if (*it == 7)

			it = vec.erase(it);

		else
			++it;
	}
	/*for (it = vec.begin(); it != vec.end(); ++it)//����ҿ�
		cout << *it << endl;*/
	//vector<int>::reverse_iterator rit;                  //�������
	// for (rit = vec.rbegin(); rit != vec.rend(); ++rit)
	//	cout << *rit << endl;
	for (auto it: vec)                          //��Χѭ��
	{
		cout << it << endl;
	}
 	return 0;
	
}
//  emplace_back();