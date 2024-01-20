//--------------------------------------------------
//	GeometryRender.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _GEOMETRYRENDER_H
#define _GEOMETRYRENDER_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IRender.h"
#include <string>

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class GeometryRender
	{
	public:
		void initialize(void);
		void shutdown(void);
		IRender* get_render(std::wstring render_type);

	private:
		IRender* _line_render = nullptr;
		IRender* _ellipse_render = nullptr;
		IRender* _rect_render = nullptr;
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_GEOMETRYRENDER_H



