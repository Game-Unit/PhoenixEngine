#include "Core/Application.h"
#include "GameScene.h"

#if !_DEBUG
#define NOGDI           
#define NOUSER  
#include <Windows.h>
#endif

#if _DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
	int main()
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
#endif
	{
		GameScene scene;

		Core::Application app;
		app.SetScene(scene);
		app.Run();
	}