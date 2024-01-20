#include "PosManager.h"
#include <iostream>
int main() 
{
	auto manager = new PosManager();
	int blockSize = 100;
	int mapSize = 10000;
	manager->init(blockSize, mapSize);

	int posId1 = 1;
	int posId2 = 2;
	manager->add(posId1, 100, 100); 
	manager->add(posId2, 20, 50);
	auto posIds = manager->find(posId1);    // 找到posid1脚下以及周围8格的所有id
	std::cout << "查找到的id" << std::endl;
	for (auto& posId : posIds)
	{
		std::cout << posId << "  ";
	}
	manager->update(posId1, 300, 400);
	manager->remove(posId2);
	posIds = manager->find(posId1);    // 找到posid1脚下以及周围8格的所有id
	std::cout << std::endl << "查找到的id" << std::endl;
	for (auto& posId : posIds)
	{
		std::cout << posId << "  ";
	}
}