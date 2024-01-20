//--------------------------------------------------
//	GeometryManager.h.
//	03/29/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _GEOMETRYMANAGER_H
#define _GEOMETRYMANAGER_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IGeometry.h"
#include <list>
#include "IGeometryIterator.h"
#include <memory>

//--------------------------------------------------
namespace geometry_drawing
{
	
	//--------------------------------------------------
	class GeometryManager
	{
		friend class GeometryIterator;
		friend class LineIterator;
		friend class EllipseIterator;
		friend class RectangleIterator;
	public:
		/* Singleton Pattern. */
		static GeometryManager* get_instance(void);
		static void destroy_instance(void);

		void add_geometry(IGeometry* geometry);
		void remove_geometry(IGeometry* geometry);
		void remove_all(void);
		std::shared_ptr<IGeometryIterator> get_geometry_iterator(void);
		std::shared_ptr<IGeometryIterator> get_line_iterator(void);
		std::shared_ptr<IGeometryIterator> get_ellipse_iterator(void);
		std::shared_ptr<IGeometryIterator> get_rect_iterator(void);
		

	private:
		GeometryManager();
		GeometryManager(GeometryManager&) = delete;
		GeometryManager(GeometryManager&&) = delete;
		GeometryManager &operator = (const GeometryManager&) = delete;
		~GeometryManager();

		

	private:
		static GeometryManager* _geometry_mgr;
		std::list<IGeometry*> _geometries;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_GEOMETRYMANAGER_H


