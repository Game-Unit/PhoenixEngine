#pragma once

#include <string>

namespace Core
{
	struct AppSpesifications
	{
		std::string Name = "Application";
		int Width = 1280;
		int Height = 720;
	};

	class Application
	{
	public:
		Application(const AppSpesifications& spesifications = AppSpesifications());
		virtual ~Application();

		void Run();
		void OnUpdate();
		void OnRender();
		void OnImGuiRender();

	private:
		AppSpesifications m_Spesifications;
		Camera2D m_camera;
	};
}