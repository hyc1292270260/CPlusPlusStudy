#include "frame_work.hpp"

//---------------------------------------------------
//	frame_workImp.inl.
//	07/28/2019.			by hyc.
//---------------------------------------------------
#pragma once

template <typename InheritedT>
inline unsigned winframework::WinFramwork <InheritedT>::run(void)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

template<typename InheritedT>
inline void winframework::WinFramwork<InheritedT>::onPaint(HDC hDC)
{
}

template<typename InheritedT>
inline void winframework::WinFramwork<InheritedT>::onLBtnDown(POINT & pt)
{
}

template<typename InheritedT>
inline void winframework::WinFramwork<InheritedT>::onLBtnUp(POINT & pt)
{
}

template<typename InheritedT>
inline void winframework::WinFramwork<InheritedT>::preCreateWin(WNDCLASSEX & wcex)
{
}
