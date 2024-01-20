//--------------------------------------------------
//	GeometryFactory.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _GEOMETRYFACTORY_H
#define _GEOMETRYFACTORY_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IGeometry.h"
#include <string>

//--------------------------------------------------
namespace geometry_drawing
{
	
	//--------------------------------------------------
	class GeometryFactory
	{
	public:
		static GeometryFactory* get_instance(void);
		static void destroy_instance(void);

		IGeometry* create_geometry(std::wstring geometry_type, int start_x, int start_y, int end_x, int end_y);

	private:
		GeometryFactory();
		GeometryFactory(GeometryFactory&) = delete;
		GeometryFactory(GeometryFactory&&) = delete;
		GeometryFactory &operator = (const GeometryFactory&) = delete;
		~GeometryFactory();

	private:
		static GeometryFactory* _geometry_factory;
	};

	//--------------------------------------------------
}


//--------------------------------------------------
#endif // !_GEOMETRYFACTORY_H







