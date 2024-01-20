//---------------------------------------------------
//	frame_work.hpp.
//	07/28/2019.			by hyc.
//---------------------------------------------------

#pragma once
#ifndef _WINFRAMEWORK_HPP
#define _WINFRAMEWORK_HPP

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
	
	extern HINSTANCE _hInstance;
	extern void* _pWinFrame;

	//---------------------------------------------------

	template <typename InheritedT>
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
		void onPaint(HDC hDC);
		void onLBtnDown(POINT& pt);
		void onLBtnUp(POINT& pt);
		void preCreateWin(WNDCLASSEX& wcex);

	private:
		static long __stdcall fnProcdure(HWND hWnd, unsigned message, unsigned wParam, long lParam);

	protected:
		HWND _hWnd;
		std::wstring _name;
		
	};

	//---------------------------------------------------
	// Implementations
	//---------------------------------------------------
#include "frame_workImp.hpp"
	//----------------------------------------------------
	// inline files
	//---------------------------------------------
#include "frame_work.inl"
}

//---------------------------------------------------
#endif // !_WINFRAMEWORK_HPP



