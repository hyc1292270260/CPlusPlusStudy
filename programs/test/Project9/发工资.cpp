#include<iostream>
#include<vector>
#include<stdlib.h>

//发奖金，每人至少100元，根据年限，A比邻座工龄长，必须多100元
using namespace std;

vector<int>vec;

int main(void)
{
	
	int N, y, sum = 0;
	cin >> N;
	if (N < 1 || N>1000)
		return -1;
	for (int i = 0; i < N; ++i)
	{

		cin >> y;
		vec.emplace_back(y);

	}
	vector<int>left_vec(vec.size(),100);
	vector<int>right_vec(vec.size(),100);
	
	for (int i = 1; i < vec.size(); ++i)
	{
		if (vec[i] > vec[i - 1])
		{
			left_vec[i] = left_vec[i - 1] + 100;				//left
		}
	}
	for (int i = vec.size() - 2; i >= 0; --i)
	{
		if (vec[i] > vec[i + 1])								//right
		{
			right_vec[i] = right_vec[i - 1] + 100;
		}
	}
	for (int i = 0; i < vec.size(); ++i)
	{
		//sum += __max(right_vec[i], left_vec[i]);
		if (left_vec[i] < right_vec[i])
		{
			sum += right_vec[i];
		}
		else
			sum += left_vec[i];
		
	}
	cout << sum << endl;
	return 0;
}