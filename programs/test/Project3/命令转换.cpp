#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;


struct order
{
	string cmd;
	string action;
};
order push_map(string s1, string s2);
string transfer(string s1);
vector<order> order_map;
vector<string> result;
vector<order>::iterator it;
int main(void)
{
	while (true)
	{
		int m, n;
		string s1, s2;
		cin >> m >> n;
		for (int i = 0; i < m; ++i)
		{
			cin >> s1 >> s2;
			order_map.emplace_back(push_map(s1, s2));    //push cmd and action into map
		}

		for (int j = 0; j < n; ++j)
		{
			cin >> s1;
			s2 = transfer(s1);
			if (s2 != "none")
				result.emplace_back(s2);

		}
		for (auto it : result)
		{
			cout << it << endl;
		}
		result.clear();
	}
	
	
	return 0;

}
order push_map(string s1,string s2)
{
	order odr;
	odr.cmd = s1;
	odr.action = s2;
	return odr;
}
string transfer(string s1)
{
	for (it = order_map.begin();it!=order_map.end();++it)    //find in map
	{
		if (s1==it->cmd)
		{
			return it->action;
		}
	}
	return "none";
}