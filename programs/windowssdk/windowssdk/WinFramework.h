//---------------------------------------------------
//	WinFramework.h.
//	03/24/2019.			by bubo.
//---------------------------------------------------
#pragma once

#ifndef _WINFRAMEWORK_H
#define _WINFRAMEWORK_H

//---------------------------------------------------
//	headers...
//---------------------------------------------------
#include <windows.h>
#include <string>
#include <memory>

//---------------------------------------------------
namespace winframework
{
	//---------------------------------------------------
	class WinFramwork
	{
		friend int __stdcall
			::wWinMain(
				HINSTANCE hInstance,
				HINSTANCE hPreInstance,
				wchar_t * lpCmdLine,
				int iCmdShow);

	public:
		WinFramwork(std::wstring name);
		 ~WinFramwork();
		void createWin();
		void showWnd(void);
		unsigned run(void);

	protected:
		virtual void onPaint(HDC hDC);
		virtual void onLBtnDown(POINT& pt);
		virtual void onLBtnUp(POINT& pt);
		virtual void preCreateWin(WNDCLASSEX& wcex);

	private:
		static long __stdcall fnProcdure(HWND hWnd, unsigned message, unsigned wParam, long lParam);

	protected:
		HWND _hWnd;
		std::wstring _name;
		static HINSTANCE _hInstance;
		static std::shared_ptr<WinFramwork> _spWinFrame;
	};

	//---------------------------------------------------
}

//---------------------------------------------------
#endif // !_WINFRAMEWORK_H


