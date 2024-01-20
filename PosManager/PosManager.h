#pragma once
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

struct PosInfo
{
	PosInfo(int x, int y) :x(x), y(y) {};
	PosInfo():x(-1),y(-1) {};
	int x;
	int y;
};
class  PosManager
{
public:
	PosManager();
	~PosManager();
	bool init(int blockSize, int mapSize);
	void add(int posId, int x, int y);
	vector<int> find(int posId);
	void update(int posId, int x, int y);
	void remove(int posId);

private:
	int getBlockIndex(int x, int y);

	int m_blockSize;
	int m_mapSize;
	vector<set<int>> m_posMap;
};

