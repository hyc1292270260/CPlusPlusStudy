
//---------------------------------------------------
//	frame_workImp.inl.
//	07/28/2019.			by hyc.
//---------------------------------------------------
#include"frame_work.hpp"
#include "myapp.h"
using namespace winframework;
//define
namespace winframework
{
	HINSTANCE _hInstance;
	void* _pWinFrame;				//万能指针强制转换
}

int __stdcall
wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, wchar_t * lpCmdLine, int iCmdShow)
{
	_hInstance = hInstance;
	return WinFramMain(lpCmdLine);
}