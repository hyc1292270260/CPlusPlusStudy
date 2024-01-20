#include "GeometryFactory.h"
#include "Ellipse.h"
#include "Line.h"
#include "Rectangle.h"

 geometry_drawing::GeometryFactory* geometry_drawing::GeometryFactory::_geometry_factory = nullptr;


 geometry_drawing::GeometryFactory::GeometryFactory()
 {

 }
geometry_drawing::GeometryFactory * geometry_drawing::GeometryFactory::get_instance(void)
{
	if (!_geometry_factory)
	{
		_geometry_factory = new GeometryFactory;
		return _geometry_factory;
	}
	return _geometry_factory;
}

void geometry_drawing::GeometryFactory::destroy_instance(void)
{
	if (!_geometry_factory)
		return;
	delete _geometry_factory;
	_geometry_factory = nullptr;
}

geometry_drawing::IGeometry * geometry_drawing::GeometryFactory::create_geometry(std::wstring geometry_type, int start_x, int start_y, int end_x, int end_y)
{
	if (geometry_type == L"Line")
	{
		return new Line(start_x, start_y, end_x, end_y);
	}
	else if (geometry_type == L"Rectangle")
	{
		return new Rectangle(start_x, start_y, end_x, end_y);
	}
	else if (geometry_type == L"Ellipse")
	{
		return new Ellipse(start_x, start_y, end_x, end_y);
	}
	else
		return nullptr;
	
}

geometry_drawing::GeometryFactory::~GeometryFactory()
{
}
