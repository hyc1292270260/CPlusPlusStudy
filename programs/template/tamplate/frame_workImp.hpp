//---------------------------------------------------
//	frame_workImp.hpp.
//	07/28/2019.			by hyc.
//---------------------------------------------------
#pragma once
#include <windowsx.h>
#include <string>
#include <memory>


using namespace winframework;

extern void* _pWinFrame;
template<typename InheritedT>
void winframework::WinFramwork<InheritedT>::createWin()
{
	_pWinFrame = this;
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &fnProcdure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(LoadCursor(NULL, WHITE_BRUSH));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _name.c_str();
	wcex.hIconSm = wcex.hIcon;
	
	if (auto inherited = static_cast<InheritedT*>(_pWinFrame))
		inherited->preCreateWin(wcex);
	if (!RegisterClassEx(&wcex))
	{
		return;
	}

	_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		_name.c_str(), L"App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, _hInstance, NULL);
}
template<typename InheritedT>
inline void winframework::WinFramwork<InheritedT>::showWnd(void)
{
	if (!_hWnd)
		return;

	ShowWindow(_hWnd, SW_NORMAL);
	UpdateWindow(_hWnd);
}
template <typename InheritedT> WinFramwork <InheritedT>:: WinFramwork(std::wstring name):_hWnd(nullptr)
{
	
	_name = std::move(name);
}

template<typename InheritedT>
inline winframework::WinFramwork<InheritedT>::~WinFramwork()
{
}





template <typename InheritedT> long __stdcall 
WinFramwork <InheritedT>::fnProcdure(HWND hWnd, unsigned message, unsigned wParam, long lParam)
{
	
		HDC hDC;
		PAINTSTRUCT ps;
		auto inherited = static_cast<InheritedT*>(_pWinFrame);
		if (!inherited)
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		switch (message)
		{
		case WM_CREATE:
		{
			return 0;
		}
		case WM_PAINT:
		{
			hDC = BeginPaint(hWnd, &ps);
			if (inherited)
				inherited->onPaint(hDC);

			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = GET_X_LPARAM(lParam);
			pt.y = GET_Y_LPARAM(lParam);
			if (inherited)
				inherited->onLBtnUp(pt);
			return 0;

		}
		case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = GET_X_LPARAM(lParam);
			pt.y = GET_Y_LPARAM(lParam);
			if (inherited)
				inherited->onLBtnUp(pt);
			return 0;

		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	
}