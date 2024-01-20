#pragma once
#include "Vec3.h"
class OctreePoint
{
public:
	OctreePoint()
	{

	}
	OctreePoint(const Vec3& pos)
	{
		m_pos = pos;
	}

	Vec3& getPosition()
	{
		return m_pos;
	}

	void setPosition(const Vec3& pos)
	{
		m_pos = pos;
	}

private:
	Vec3 m_pos;
	// 可以有其它数据
};
