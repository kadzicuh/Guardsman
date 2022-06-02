#include <Windows.h>
#include <tchar.h>
#include "SearchEngine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	SearchEngine engine;
	engine.Start();
}