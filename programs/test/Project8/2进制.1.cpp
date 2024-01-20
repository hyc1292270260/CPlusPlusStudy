#/*#include<iostream>
#include<vector>
#include<set>
using namespace std;

unsigned long long int transfer_num(unsigned long long int x);

vector<unsigned long long int>vec;
set<unsigned long long int>_set;
int main(void)
{
	int T, N;
	unsigned long long int a;
	cin >> T;
	if (T <= 0 || T > 10)
		return -1;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		if (N <= 0 || N > 100)
			return -1;
		for (int j = 0; j < N; ++j)
		{
			cin >> a;
			vec.emplace_back(a);

		}
		for (int j = 0; j < N; ++j)
		{
			int b = transfer_num(vec[j]);
			_set.insert(b);

		}
		cout << _set.size() << endl;
	}
	return 0;
}
unsigned long long int transfer_num(unsigned long long int x)
{
	unsigned long long int  count = 0ull;
	while (x > 0)
	{
		if (x & 1)
			++count;
		x >>= 1;
	}
	return count;
}*/