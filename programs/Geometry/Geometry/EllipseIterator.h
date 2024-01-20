//--------------------------------------------------
//	EllipseIterator.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _ELLIPSEITERATOR_H
#define _ELLIPSEITERATOR_H

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
	class EllipseIterator : public IGeometryIterator
	{
	public:
		EllipseIterator(GeometryManager* mgr);
		virtual IGeometry* current(void) ;
		virtual void move_next(void);
		virtual bool has_next(void) ;
	private:
		std::list<IGeometry*>::iterator _current_it;
		GeometryManager* _mgr = nullptr;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_ELLIPSEITERATOR_H





