#include "GeometryIterator.h"
#include "GeometryManager.h"

geometry_drawing::GeometryIterator::GeometryIterator(GeometryManager * mgr)
{
	if (!mgr)
	{
		return ;
	}
	_mgr = mgr;
	_current_it = mgr->_geometries.begin();

}

geometry_drawing::IGeometry * geometry_drawing::GeometryIterator::current(void)
{
	if (!_mgr)
	{
		return nullptr;
	}
	if (_current_it != _mgr->_geometries.end())
	{
		return *_current_it;
	}
	else
		return nullptr;
	
}

void geometry_drawing::GeometryIterator::move_next(void)
{
	++_current_it;
}

bool geometry_drawing::GeometryIterator::has_next(void)
{
	if (!_mgr)
	{
		return false;
	}
	return  _current_it == _mgr->_geometries.end() ? false : true;
}
