//--------------------------------------------------
//	IGeometry.h.
//	03/29/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _IGEOMETRY_H
#define _IGEOMETRY_H

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class IGeometry
	{
	public:
		virtual int get_start_x(void) const = 0;
		virtual int get_start_y(void) const = 0;
		virtual int get_end_x(void) const = 0;
		virtual int get_end_y(void) const = 0;
	
	
     private:

	int _start_x;
	int _start_y;
	int _end_x;
	int _end_y;

	
	};
}


//--------------------------------------------------
#endif // !_IGEOMETRY_H




