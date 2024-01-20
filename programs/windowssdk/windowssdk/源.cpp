//#include "WinFramework.h"
//
//using namespace winframework;
//
//int WinFramMain(std::wstring parameter)
//{
//	WinFramwork frame(L"FirstApp");
//	frame.showWnd();
//	return frame.run();
//}
#include "myApp.h"

using namespace winframework;

int WinFramMain(std::wstring parameter)
{
	MyApp myapp;
	myapp.createWin();
	myapp.showWnd();
	return myapp.run();
}
