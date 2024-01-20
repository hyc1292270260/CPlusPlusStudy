#include<iostream>
using namespace std;

template<typename T,typename T1>

class oper
{
public:
	T add(T a, T b)
	{
		return a + b;
	}
	T1 add(T a, T1 b)
	{
		return a + b;
	}




};

int main(void)   
{
	oper<int, float> a ;
	int result1 = a.add(3, 5); 
	cout<< result1 << endl;
	float result2 = a.add(3, 5.4f);
	cout << result2 << endl;
	

	return 0;

}