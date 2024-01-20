//--------------------------------------------------
//	Rectangle.h.
//	03/29/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IGeometry.h"

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class Rectangle : public IGeometry
	{
	public:
		Rectangle(int start_x, int start_y, int end_x, int end_y);
		virtual int get_start_x(void) const;
		virtual int get_start_y(void) const;
		virtual int get_end_x(void) const;
		virtual int get_end_y(void) const;

	private:
		int _start_x;
		int _start_y;
		int _end_x;
		int _end_y;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_RECTANGLE_H



