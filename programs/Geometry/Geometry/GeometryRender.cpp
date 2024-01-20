#include "GeometryRender.h"
#include "EllipseRender.h"
#include "RectangleRender.h"
#include "LineRender.h"


void geometry_drawing::GeometryRender::initialize(void)
{
	_line_render = new LineRender;
	_rect_render = new RectangleRender;
	_ellipse_render = new EllipseRender;
}

void geometry_drawing::GeometryRender::shutdown(void)
{
	if (_line_render)
	{
		delete _line_render;
		_line_render = nullptr;
	}
	if (_rect_render)
	{
		delete _rect_render;
		_rect_render = nullptr;
	}
	if (_ellipse_render)
	{
		delete _ellipse_render;
		_ellipse_render = nullptr;
	}
}

geometry_drawing::IRender * geometry_drawing::GeometryRender::get_render(std::wstring render_type)
{
	if (render_type == L"Line")
		return _line_render;
	else if (render_type == L"Ellipse")
		return _ellipse_render;
	else if (render_type == L"Rectangle")
		return _rect_render;
	else
		return nullptr;

}
