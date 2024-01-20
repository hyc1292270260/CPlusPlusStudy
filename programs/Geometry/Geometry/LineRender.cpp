#include "LineRender.h"
#include "IGeometry.h"

void geometry_drawing::LineRender::render(HDC hDC, IGeometry * geometry)
{
	if (!hDC || !geometry)
		return;
	::MoveToEx(hDC, geometry->get_start_x(), geometry->get_start_y(),nullptr);
	::LineTo(hDC, geometry->get_end_x(), geometry->get_end_y());
}