#include<iostream>
#include<vector>
#include<math.h>
#include <algorithm>
using namespace std;


struct _result
{
	long long int abs_result;
	int pre_index;
	int back_index;
};
vector<long long int>vec;
vector<_result>result_vec;
vector<long long int>abs_vec;


vector<long long int> insert_sort(vector<long long int>abs_vec, int n);
int main(void)
{
	_result r;
	int n;
	long long int a;
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		cin >> a;
		vec.emplace_back(a);
	}
	for (int j = 1; j < n; ++j)
	{
		long long int abs_result = abs(vec[j] - vec[j - 1]);
		
		r.abs_result = abs_result;
		r.back_index = j ;
		r.pre_index = j - 1;
		result_vec.emplace_back(r);
		abs_vec.emplace_back(r.abs_result);      //push result into map
	}

	abs_vec = insert_sort(abs_vec, abs_vec.size());  //sort abs
	a = abs_vec[0];
	for (auto it:result_vec)
	{
		if (it.abs_result == a)      //the min
		{
			cout << vec[it.pre_index] << " "<< vec[it.back_index] << endl;
			return 0;
		}
	}
	

		return 0;
}

vector<long long int> insert_sort(vector<long long int>abs_vec, int n)
{
	int j;
	long long int  temp;
	for (int i = 1; i < n; ++i)
	{
		temp = abs_vec[i]; 
		for (j = i - 1; j >= 0 && abs_vec[j] > temp; j--)
		{
			abs_vec[j + 1] = abs_vec[j];
		}
		abs_vec[j + 1] = temp;
	}
	return abs_vec;
}