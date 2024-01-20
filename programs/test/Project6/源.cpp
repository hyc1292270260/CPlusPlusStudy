#include<iostream>
#include<vector>

using namespace std;
vector<long long int>vec;
int main(void)
{
	int n, num=0;
	long long int a;
	cin >> n;


	for (int i = 0; i < n; ++i)
	{
		cin >> a;
		vec.emplace_back(a);
	}
	for (int j = 0; j < n; ++j)
	{
		for (int i = 0; i < n - j - 1; ++i)
		{
			int temp = vec[j] > vec[i + 1] ? vec[j] : vec[j + 1];
			if (temp * 0.9 <= vec[j + 1] && temp*0.9 <= vec[j])
			{
				num++;
			}

		}

	}
	cout << num << endl;
	return 0;

}