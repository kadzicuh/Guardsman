#include <Windows.h>
#include <tchar.h>
//#include <iostream>
//#include "Utils.h"
#include "SearchEngine.h"

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
int _tmain(int argc, TCHAR* argv[])
{
	//std::cout << Utils::DirectoryExists(_T("F:\\"));
	SearchEngine engine;
	engine.Start();
}