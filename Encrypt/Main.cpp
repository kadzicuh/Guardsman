#include <Windows.h>
#include <tchar.h>
#include "SearchEngine.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow)
{
    SearchEngine engine;
    engine.Start();
}