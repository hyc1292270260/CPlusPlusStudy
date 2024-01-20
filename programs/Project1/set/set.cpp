#include<iostream>
#include<set>             
#include<algorithm>

int main(void)
{
	std::set<int>my_set;       //值与键相同，只能有一个
	my_set.insert(2);
	my_set.insert(1);
	my_set.insert(3);
	my_set.insert(3);

	for (auto it : my_set)           
		std::cout << it << std::endl;
	return 0;
}