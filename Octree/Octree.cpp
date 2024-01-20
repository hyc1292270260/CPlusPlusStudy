#include "Vec3.h"
#include "Octree.h"
#include <vector>

const char X_MASK = 0b100;
const char Y_MASK = 0b010;
const char Z_MASK = 0b001;
Octree::Octree(const Vec3& center, const Vec3& halfLength) :m_center(center), m_halfLength(halfLength)
{
	for (int i = 0; i < 8; ++i)
		m_children[i] = nullptr;
}

Octree::~Octree()
{
	for (int i = 0; i < 8; ++i)
	{
		delete m_children[i];
		m_children[i] = nullptr;
	}
}

bool Octree::isLeafNode() const
{
	// all or none
	return m_children[0] == nullptr;
}

void Octree::insert(OctreePoint* point)
{
	if (point == nullptr)	return;

	if (isLeafNode())
	{
		if (!m_data)
			m_data = point;
		else
		{
			// 拆分节点
			OctreePoint* oldPoint = m_data;
			m_data = nullptr;
			for (int i = 0; i < 8; ++i)
			{
				Vec3 newCenter = m_center;
				newCenter.x += m_halfLength.x * (i & X_MASK ? 0.5f : -0.5f);
				newCenter.y += m_halfLength.y * (i & Y_MASK ? 0.5f : -0.5f);
				newCenter.z += m_halfLength.z * (i & Z_MASK ? 0.5f : -0.5f);
				m_children[i] = new Octree(newCenter, m_halfLength * 0.5f);
			}
			//原来的节点位置
			m_children[getPointPositionDir(oldPoint->getPosition())]->insert(oldPoint);
			//新的节点位置
			m_children[getPointPositionDir(point->getPosition())]->insert(point);
		}
	}
	else
	{
		m_children[getPointPositionDir(point->getPosition())]->insert(point);
	}
}

int Octree::getPointPositionDir(const Vec3& point) const
{
	int dir = 0;
	if (point.x >= m_center.x) dir |= X_MASK;
	if (point.y >= m_center.y) dir |= Y_MASK;
	if (point.z >= m_center.z) dir |= Z_MASK;
	return dir;
}

void Octree::getPointsInsideBox(Vec3& bmin, Vec3& bmax, std::vector<OctreePoint*>& results)
{
	if (isLeafNode())
	{
		if (m_data != nullptr)
		{
			const Vec3& pos = m_data->getPosition();
			if (pos.x > bmax.x || pos.y > bmax.y || pos.z > bmax.z) return;
			if (pos.x < bmin.x || pos.y < bmin.y || pos.z < bmin.z) return;
			results.push_back(m_data);
		}
	}
	else
	{
		for (int i = 0; i < 8; ++i) {
			//最大点
			Vec3 cmax = m_children[i]->m_center + m_children[i]->m_halfLength;
			//最小点
			Vec3 cmin = m_children[i]->m_center - m_children[i]->m_halfLength;

			if (cmax.x < bmin.x || cmax.y < bmin.y || cmax.z < bmin.z) continue;
			if (cmin.x > bmax.x || cmin.y > bmax.y || cmin.z > bmax.z) continue;

			m_children[i]->getPointsInsideBox(bmin, bmax, results);
		}
	}

}
