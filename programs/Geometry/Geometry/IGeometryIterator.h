//--------------------------------------------------
//	IGeometryIterator.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _IGEOMETRYITERATOR_H
#define _IGEOMETRYITERATOR_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IGeometry.h"

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class IGeometryIterator
	{
	public:
		virtual IGeometry* current(void) = 0;
		virtual void move_next(void) = 0;
		virtual bool has_next(void) = 0;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_IGEOMETRYITERATOR_H




