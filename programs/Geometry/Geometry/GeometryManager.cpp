#include "GeometryManager.h"
#include "GeometryIterator.h"
#include "EllipseIterator.h"
#include "LineIterator.h"
#include "RectangleIterator.h"

using namespace geometry_drawing;
 GeometryManager* GeometryManager::_geometry_mgr = nullptr;

 GeometryManager::GeometryManager()
 {

 }
GeometryManager* GeometryManager::get_instance(void)
{
	if (! _geometry_mgr)
	{
		_geometry_mgr = new GeometryManager;
		return _geometry_mgr;
	}
	return _geometry_mgr;
}

void geometry_drawing::GeometryManager::destroy_instance(void)
{
	if (_geometry_mgr)
	{
		_geometry_mgr = nullptr;
		delete _geometry_mgr;
	}
}

void geometry_drawing::GeometryManager::add_geometry(IGeometry * geometry)
{
	if (!geometry)
		return;
	_geometries.emplace_back(geometry);
}

void geometry_drawing::GeometryManager::remove_geometry(IGeometry * geometry)
{
	if (!geometry)
		return;
	for (std::list<IGeometry*>::iterator it = _geometries.begin();it!=_geometries.end();)
	{
		if (*it == geometry)
		{
			delete *it;
			_geometries.erase(it);
		}
		else
			++it;
	}
	

}



void geometry_drawing::GeometryManager::remove_all(void)
{
	
	/*for (std::list<IGeometry*>::iterator it = _geometries.begin(); it != _geometries.end();++it)
	{
			delete *it;
			_geometries.erase(it);

	}*/
	for (auto it : _geometries)
		delete it;
	_geometries.clear();
}

geometry_drawing::GeometryManager::~GeometryManager()
{
}

std::shared_ptr<IGeometryIterator> geometry_drawing::GeometryManager::get_geometry_iterator(void)
{
	return std::shared_ptr<IGeometryIterator>(new GeometryIterator(this));
}

std::shared_ptr<IGeometryIterator> geometry_drawing::GeometryManager::get_line_iterator(void)
{
	return std::shared_ptr<IGeometryIterator>();
}

std::shared_ptr<IGeometryIterator> geometry_drawing::GeometryManager::get_ellipse_iterator(void)
{
	return std::shared_ptr<IGeometryIterator>();
}

std::shared_ptr<IGeometryIterator> geometry_drawing::GeometryManager::get_rect_iterator(void)
{
	return std::shared_ptr<IGeometryIterator>();
}
