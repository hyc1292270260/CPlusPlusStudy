#include "EllipseRender.h"
#include "IGeometry.h"

void geometry_drawing::EllipseRender::render(HDC hDC, IGeometry * geometry)
{
	if (!hDC || !geometry)
		return;
	::Ellipse(hDC, geometry->get_start_x(), geometry->get_start_y(), geometry->get_end_x(), geometry->get_end_y());
}