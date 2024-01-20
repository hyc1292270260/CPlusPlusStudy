//--------------------------------------------------
//	GeometryIterator.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _GEOMETRYITERATOR_H
#define _GEOMETRYITERATOR_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IGeometryIterator.h"
#include <list>

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	//	incomplete type.
	//--------------------------------------------------
	class GeometryManager;

	//--------------------------------------------------
	class GeometryIterator : public IGeometryIterator
	{
	public:
		GeometryIterator(GeometryManager* mgr);
		virtual IGeometry* current(void);
		virtual void move_next(void);
		virtual bool has_next(void);

	private:
		std::list<IGeometry*>::iterator _current_it;
		GeometryManager* _mgr = nullptr;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_GEOMETRYITERATOR_H





