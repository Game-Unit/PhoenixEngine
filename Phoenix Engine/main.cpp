#include "Application.h"
#include <Windows.h>

#if _DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
	int main()
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
#endif
	{
	Core::Application app;
	app.Run();
	}