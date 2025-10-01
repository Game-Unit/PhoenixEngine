#include "Application.h"
#include "rlImGui.h"
#include "Debug.h"

#if _DEBUG
#include "../EditorScene.h"
#include "../GameScene.h"
#endif

#include <iostream>

Camera2D Core::Application::m_camera = Camera2D();

Core::Application::Application(const AppSpesifications& spesifications) : m_appSpesifications(spesifications)
{	
}

Core::Application::~Application()
{
}

void Core::Application::Run()
{
	if (m_scene == nullptr)
	{
		Debug::LogError("Must add a starting scene to AppSpesifications");
		std::cin.get();
		return;
	}

	const int w = m_appSpesifications.Width;
	const int h = m_appSpesifications.Height;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(w, h, m_appSpesifications.name.c_str());
	rlImGuiSetup(true);

	m_camera.target = Vector2(0, 0);
	m_camera.offset = Vector2{ w / 2.0f, h / 2.0f };
	m_camera.rotation = 0.0f;
	m_camera.zoom = 1.0f;

	m_scene->OnStart();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// Raylib
		BeginDrawing();

		ClearBackground(WHITE);

		// Raylib Camera
		BeginMode2D(m_camera);

		m_scene->OnUpdate();

		EndMode2D();

		// ImGui
		rlImGuiBegin();
		m_scene->OnImGuiRender();
		rlImGuiEnd();

#if _DEBUG
		if (IsKeyPressed(KEY_TAB))
		{
			if (m_inEditor)
			{
				GameScene gameScene;
				SetScene(gameScene);
				m_inEditor = false;
			}
			else
			{
				EditorScene EditorScene;
				SetScene(EditorScene);
				m_inEditor = true;
			}
		}
#endif

		EndDrawing();
	}
	rlImGuiShutdown();
	CloseWindow();
}
