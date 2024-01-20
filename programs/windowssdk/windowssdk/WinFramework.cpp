//---------------------------------------------------
//	WinFramework.cpp.
//	03/24/2019.			by bubo.
//---------------------------------------------------
#include "WinFramework.h"
#include<Windowsx.h>
//---------------------------------------------------
//	initialize static variables...
//---------------------------------------------------
HINSTANCE winframework::WinFramwork::_hInstance = nullptr;
std::shared_ptr <winframework::WinFramwork> winframework::WinFramwork::_spWinFrame;

//---------------------------------------------------
int WinFramMain(std::wstring parameter);

//---------------------------------------------------
winframework::WinFramwork::WinFramwork(std::wstring name) :_hWnd(nullptr)
{
	_spWinFrame.reset(this);
	_name = std::move(name);
}

//---------------------------------------------------
winframework::WinFramwork::~WinFramwork()
{
	if (!_spWinFrame)
		return;
}

void winframework::WinFramwork::createWin()
{
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
	//构造函数不能调用虚函数表
	if (_spWinFrame)
		_spWinFrame->preCreateWin(wcex);
	if (!RegisterClassEx(&wcex))
	{
		return;
	}

	_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		_name.c_str(), L"App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, _hInstance, NULL);
}

//---------------------------------------------------
void
winframework::WinFramwork::showWnd(void)
{
	if (!_hWnd)
		return;

	ShowWindow(_hWnd, SW_NORMAL);
	UpdateWindow(_hWnd);
}

//---------------------------------------------------
unsigned
winframework::WinFramwork::run(void)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



void winframework::WinFramwork::onPaint(HDC hDC)
{
	return;
}

void winframework::WinFramwork::onLBtnDown(POINT & pt)
{
	return;
}

void winframework::WinFramwork::onLBtnUp(POINT & pt)
{
	return;
}

void winframework::WinFramwork::preCreateWin(WNDCLASSEX & wcex)
{
	
}




//---------------------------------------------------
long __stdcall
winframework::WinFramwork::fnProcdure(
	HWND hWnd,
	unsigned message,
	unsigned wParam,
	long lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
	{
		return 0;
	}
	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);
		if(_spWinFrame)
		   _spWinFrame->onPaint(hDC);
		
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		POINT pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		if (_spWinFrame)
			_spWinFrame->onLBtnUp(pt);
		return 0;

	}
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		if (_spWinFrame)
			_spWinFrame->onLBtnUp(pt);
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

//---------------------------------------------------
int __stdcall
wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	wchar_t * lpCmdLine,
	int iCmdShow)
{
	winframework::WinFramwork::_hInstance = hInstance;
	return ::WinFramMain(lpCmdLine);
}

//---------------------------------------------------






