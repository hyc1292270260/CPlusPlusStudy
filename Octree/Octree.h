#pragma once
#include "Vec3.h"
#include "OctreePoint.h"
#include <vector>
class Octree
{
public:
	Octree(const Vec3& center, const Vec3& halfLength);
	~Octree();

	void insert(OctreePoint* point);
	int getPointPositionDir(const Vec3& point) const;
	void getPointsInsideBox(Vec3& bmin, Vec3& bmax, std::vector<OctreePoint*>& results);

private:
	bool isLeafNode() const;

	Vec3 m_center;
	Vec3 m_halfLength;
	Octree* m_children[8];
	OctreePoint* m_data = nullptr;

	//child:	0 1 2 3 4 5 6 7
	//x :		- - - - + + + +
	//y :		- - + + - - + +
	//z :		- + - + - + - +
};