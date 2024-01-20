//--------------------------------------------------
//	RectangleRender.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _RECTANGLERENDER_H
#define _RECTANGLERENDER_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IRender.h"

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class RectangleRender : public IRender
	{
	public:
		virtual void render(HDC hDC, IGeometry* geometry);
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_RECTANGLERENDER_H






