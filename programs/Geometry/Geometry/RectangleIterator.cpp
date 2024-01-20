#include "RectangleIterator.h"
#include "GeometryManager.h"
#include "Rectangle.h"


geometry_drawing::RectangleIterator::RectangleIterator(GeometryManager * mgr)
{
	if (!mgr)
	{
		return;
	}
	_mgr = mgr;
	_current_it = mgr->_geometries.begin();

}

geometry_drawing::IGeometry * geometry_drawing::RectangleIterator::current(void)
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

void geometry_drawing::RectangleIterator::move_next(void)
{
	do
	{
		++_current_it;
	} while (typeid(**_current_it) != typeid(Rectangle) && _current_it != _mgr->_geometries.end());
}

bool geometry_drawing::RectangleIterator::has_next(void)
{
	if (!_mgr)
	{
		return false;
	}
	auto current_it = _current_it;
	do
	{
		++current_it;
	} while (typeid(**current_it) != typeid(Rectangle) && _current_it != _mgr->_geometries.end());

	return  current_it == _mgr->_geometries.end() ? false : true;
}
