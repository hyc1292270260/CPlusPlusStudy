#include<iostream>
#include<vector>
#include<set>
#include <string>
using namespace std;

void transfer_num(unsigned int x);

vector<unsigned int>vec;
set<unsigned int>_set;
int main(void)
{
	int m, n;
	unsigned int a;
	cin >> m;
	for (int i = 0; i < m; i++)

	{
		cin >> n;
		for (int j = 0; j < n; ++j)
		{
			cin >> a;
			vec.emplace_back(a);

		}
		for (int j = 0; j < n; ++j)
		{
			transfer_num(vec[j]);


		}
		cout << _set.size() << endl;
	}
	return 0;
}

void transfer_num(unsigned int x)
{

	unsigned long long int p = 1ull, y = 0ull, temp;
	int count = 0;
	while (true)
	{
		temp = x % 2;
		x /= 2;
		y += temp * p;
		p *= 10;
		if (x < 2)
		{
			y += x * p;
			break;
		}
	}

	string s = to_string(y);
	for (auto it : s)
	{
		if (it == '1')
		{
			++count;
		}
	}
	_set.insert(count);

}