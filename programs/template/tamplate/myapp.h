#pragma once
#include "frame_work.hpp"
int WinFramMain(std::wstring parameter);
class MyApp : public winframework::WinFramwork<MyApp>
{
public:
	MyApp() :WinFramwork(L"MyApp") {}
	void preCreateWin(WNDCLASSEX &wcex)
	{
		wcex.hbrBackground = (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	void onPaint(HDC hDC)
	{
		if (!hDC)
			return;
		::Rectangle(hDC, 100, 100, 200, 200);
	}
};
