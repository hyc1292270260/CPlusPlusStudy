//--------------------------------------------------
//	EllipseRender.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _ELLIPSERENDER_H
#define _ELLIPSERENDER_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IRender.h"

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class EllipseRender : public IRender
	{
	public:
		virtual void render(HDC hDC, IGeometry* geometry);
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_ELLIPSERENDER_H






