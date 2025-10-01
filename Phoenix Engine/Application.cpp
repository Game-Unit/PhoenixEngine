#include "Application.h"
#include "raylib.h"
#include "rlImGui.h"

Core::Application::Application(const AppSpesifications& spesifications) : m_Spesifications(spesifications)
{
}

Core::Application::~Application()
{
}

void Core::Application::Run()
{
	const int w = m_Spesifications.Width;
	const int h = m_Spesifications.Height;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(w, h, m_Spesifications.Name.c_str());
	rlImGuiSetup(true);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// Raylib
		BeginDrawing();

		ClearBackground(WHITE);

		// ImGui
		rlImGuiBegin();
		OnImGuiRender();
		rlImGuiEnd();

		// Raylib Camera
		BeginMode2D(m_camera);

		OnRender();
		OnUpdate();

		EndMode2D();

		EndDrawing();
	}
	rlImGuiShutdown();
	CloseWindow();
}

void Core::Application::OnRender()
{
}

void Core::Application::OnImGuiRender()
{
}

void Core::Application::OnUpdate()
{
}
