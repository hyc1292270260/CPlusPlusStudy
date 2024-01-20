//--------------------------------------------------
//	LineRender.h.
//	03/30/2019.			by bubo.
//--------------------------------------------------
#pragma once

#ifndef _LINERENDER_H
#define _LINERENDER_H

//--------------------------------------------------
//	headers...
//--------------------------------------------------
#include "IRender.h"

//--------------------------------------------------
namespace geometry_drawing
{
	//--------------------------------------------------
	class LineRender : public IRender
	{
	public:
		virtual void render(HDC hDC, IGeometry* geometry);
	};

	//--------------------------------------------------
}

//--------------------------------------------------
#endif // !_LINERENDER_H






