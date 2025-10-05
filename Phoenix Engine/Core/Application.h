#pragma once

#include "raylib.h"
#include "Scene.h"

#include <string>

namespace Core
{
	struct AppSpesifications
	{
		std::string name = "Application";
		int Width = 1280;
		int Height = 720;
	};

	class Application
	{
	public:
		static Camera2D m_camera;

		Application(const AppSpesifications& spesifications = AppSpesifications());
		virtual ~Application();

		void Run();

		void SetScene(Scene& scene) { m_scene = &scene; }

	private:
		AppSpesifications m_appSpesifications;
		Scene* m_scene;

#if _DEBUG
		bool m_inEditor = true;
#endif
	};
}