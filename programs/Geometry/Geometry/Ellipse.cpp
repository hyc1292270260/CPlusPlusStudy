#include "Ellipse.h"

geometry_drawing::Ellipse::Ellipse(int start_x, int start_y, int end_x, int end_y)
{
	_start_x = start_x;
	_start_y = start_y;
	_end_x = end_x;
	_end_y = end_y;
}

int geometry_drawing::Ellipse::get_start_x(void) const
{
	return _start_x;
}

int geometry_drawing::Ellipse::get_start_y(void) const
{
	return _start_y;
}

int geometry_drawing::Ellipse::get_end_x(void) const
{
	return _end_x;
}

int geometry_drawing::Ellipse::get_end_y(void) const
{
	return _end_y;
}
