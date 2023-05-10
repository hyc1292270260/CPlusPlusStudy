#include "CustomVector.hpp"
#include "CustomList.hpp"
#include <iostream>
#include <vector>

int main()
{
	auto arr = CustomVector<int>();
	arr.push(2);
	arr.push(22);
	arr.push(6);
	arr.push(7);
	arr.printAll();
	arr.reserve(4);
	arr.push(20);
	arr.printAll();
	arr.insert(3, 1);
	arr.printAll();
	arr.remove(2);
	arr.printAll();
	arr.pop();
	arr.printAll();
	arr.clear();
	arr.printAll();
	int index = arr.findIndex(2);

	auto list = CustomList<int>();
	auto node1 = list.push(1);
	list.push(2);
	list.push(3);
	list.push(4);
	list.printAll();
	auto ret = list.find(2);
	list.insert(node1, 3);
	list.printAll();
	list.remove(node1);
	list.printAll();
	list.popAll();
	list.printAll();
}

