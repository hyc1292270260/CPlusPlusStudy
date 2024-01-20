#include "PosManager.h"
#include <Math.h>
#include <cassert>

PosManager::PosManager()
{
	m_blockSize = 0;
	m_mapSize = 0;
}

PosManager::~PosManager()
{
	m_posMap.clear();
}

bool PosManager::init(int blockSize, int mapSize)
{
	if (blockSize <= 0 || mapSize <= 0)
		return false;
	m_blockSize = blockSize;
	m_mapSize = mapSize;
	m_posMap.resize(mapSize);
	return true;
}

void PosManager::add(int posId, int x, int y)
{
	int blockId = getBlockIndex(x, y);
	m_posMap[blockId].insert(posId);
}

vector<int> PosManager::find(int posId)
{
	set<int> result;
	int x = 0, y = 0;
	for (auto& block : m_posMap) 
	{
		if (block.find(posId) != block.end())
		{
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					int blockX = x + i;
					int blockY = y + j;
					if (blockX < 0 || blockX >= m_mapSize / m_blockSize)
						continue;
					if (blockY < 0 || blockY >= m_mapSize / m_blockSize)
						continue;
					int blockId = blockX + blockY * (m_mapSize / m_blockSize);
					for (auto& pos : m_posMap[blockId])
						result.insert(pos);
				}
			}
			break;
		}
		x++;
		if (x >= m_mapSize / m_blockSize)
		{
			x = 0;
			y++;
		}
	}

	vector<int> resultArray;
	resultArray.resize(result.size());
	int i = 0;
	for (auto& pos : result) {
		resultArray[i++] = pos;
	}
	return resultArray;
}

void PosManager::update(int posId, int x, int y)
{
	remove(posId);
	add(posId, x, y);
}

void PosManager::remove(int posId)
{
	for (auto& block : m_posMap)
		block.erase(posId);
}

int PosManager::getBlockIndex(int x, int y)
{
	return (y / m_blockSize) * (m_mapSize / m_blockSize) + (x / m_blockSize);
}

