#include <string>
#include<unordered_map>
#include <iostream>
using namespace std;

unordered_map<char,int> my_map;

int main(void)
{
	
	string str = "addabbeeccdttdaza";
	int len = str.length();
	pair<char,int>my_pair;
	for (int i=0;i<len;++i)
	{
		
		my_pair.first = str[i];
		my_pair.second = i;
		my_map.emplace(my_pair);
	}
	for (auto it:my_map)
	{
		cout << it.first;
	}

	return 0;
}
