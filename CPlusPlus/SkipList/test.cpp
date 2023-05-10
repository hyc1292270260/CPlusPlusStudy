#include "SkipList.h"
#include <iostream>
int main()
{
	SkipList skiplist = SkipList();
	skiplist.add(1);
	skiplist.add(2);
	skiplist.add(3);
	bool b1 = skiplist.search(0);
	skiplist.add(0);
	bool b2 = skiplist.search(1);
	bool b3 = skiplist.search(0);
	skiplist.erase(0);
	skiplist.erase(1);
	bool b4 = skiplist.search(1);
	bool b5 = skiplist.search(0);

	std::cout << b1 << std::endl << b2 << std::endl << b3 << std::endl << b4 << std::endl << b5 << std::endl;
	return 0;
}

