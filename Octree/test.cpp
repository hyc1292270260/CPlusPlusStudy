#include "Vec3.h"
#include "Octree.h"
#include <vector>
#include <iostream>
std::vector<Vec3> points;
Octree* octree;
OctreePoint* octreePoints;
Vec3 qmin, qmax;

bool naivePointInBox(const Vec3& point, const Vec3& bmin, const Vec3& bmax) {
	return
		point.x >= bmin.x &&
		point.y >= bmin.y &&
		point.z >= bmin.z &&
		point.x <= bmax.x &&
		point.y <= bmax.y &&
		point.z <= bmax.z;
}

float rand11() // Random number between [-1,1]
{
	return  (2.f * rand()) * (1.f / RAND_MAX) - 1.f;
}

Vec3 randVec3() // Random vector with components in the range [-1,1]
{
	return Vec3(rand11(), rand11(), rand11());
}


void octreeInit() {
	octree = new Octree(Vec3(0, 0, 0), Vec3(1, 1, 1));
	qmin = Vec3(-.5, -.5, -.5);
	qmax = Vec3(.5, .5, .5);

	const int nPoints = 100;
	for (int i = 0; i < nPoints; ++i) {
		points.push_back(randVec3());
	}
	printf("testOctree found %u points .\n", points.size());
	fflush(stdout);

	octreePoints = new OctreePoint[nPoints];
	for (int i = 0; i < nPoints; ++i) {
		printf("octreePoints x=%f,y=%f,z=%f\n", points[i].x, points[i].y, points[i].z);
		octreePoints[i].setPosition(points[i]);
		octree->insert(octreePoints + i);
	}
	std::cout << "Inserted points to octree" << std::endl;
	fflush(stdout);
}

void testNaive() {
	std::vector<int> results;
	for (int i = 0; i < points.size(); ++i) {
		if (naivePointInBox(points[i], qmin, qmax)) {
			results.push_back(i);
		}
	}
	printf("testOctree found %u points in testNaive.\n", results.size());
	fflush(stdout);

}

void testOctree() {
	std::vector<OctreePoint*> results;
	octree->getPointsInsideBox(qmin, qmax, results);

	printf("testOctree found %u points in testOctree.\n", results.size());
}


int main()
{
	octreeInit();
	testNaive();
	testOctree();
}