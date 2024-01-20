//--------------------------------------------------
//	RectangleIterator.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _RECTANGLEITERATOR_H
#define _RECTANGLEITERATOR_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IGeometryIterator.h"
#include <list>

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class GeometryManager;
	class RectangleIterator : public IGeometryIterator
	{
	public:
		RectangleIterator(GeometryManager* mgr);
		virtual IGeometry* current(void) ;
		virtual void move_next(void) ;
		virtual bool has_next(void) ;
	private:
		std::list<IGeometry*>::iterator _current_it;
		GeometryManager* _mgr = nullptr;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_RECTANGLEITERATOR_H





