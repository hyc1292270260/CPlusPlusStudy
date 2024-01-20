#include "myApp.h"

using namespace winframework;

int WinFramMain(std::wstring parameter)
{
	WinFramwork<MyApp>* myapp = new WinFramwork<MyApp>(L"myapp");
	myapp->createWin();
	myapp->showWnd();
	return myapp->run();
}
