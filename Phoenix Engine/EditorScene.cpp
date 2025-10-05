#include "EditorScene.h"
#include "imgui.h"
#include "rlImGui.h"
#include "raylib.h"
#include "Core/Debug.h"
#include "Core/Application.h"
#include "Core/Random.h"

#include <string>
#include <algorithm>

#define CAMERA Core::Application::m_camera

EditorScene::EditorScene()
{
	// camera
	m_cameraMovement = new CameraMovement();

	// grid
	m_grid = new FallingSand::Grid(m_gridPosX, m_gridPosY, m_gridColumns, m_gridRows, m_cellSize);

	// drawing tool
	m_drawingTool = new FallingSand::DrawingTool(m_grid);
}


void EditorScene::OnStart()
{
	
}


EditorScene::~EditorScene()
{
	
}

void EditorScene::OnUpdate()
{
	// Camera
	if (!ImGui::GetIO().WantCaptureMouse)
		m_cameraMovement->Update();

	// Grid
	if (IsKeyPressed(KEY_SPACE))
	{
		FallingSand::Solid* solid = new FallingSand::Solid(0, 0, m_grid);
		m_grid->AddElement(solid);
	}

	if (m_draw)
	{
		m_drawingTool->ChangeShape(m_drawShape);
		m_drawingTool->ChangeElement(m_drawElement);
		m_drawingTool->SetDrawSize(m_drawSize);

		m_drawingTool->Update();
		if (IsMouseButtonDown(0) && !ImGui::GetIO().WantCaptureMouse)
		{
			Vector2 mousePosWorld = GetScreenToWorld2D(GetMousePosition(), CAMERA);
			Vector2 gridPos = m_grid->WorldToGrid(mousePosWorld);

			if (!m_erase)
			{
				Color rayColor = {
					(unsigned char)(m_imDrawColor[0] * 255),
					(unsigned char)(m_imDrawColor[1] * 255),
					(unsigned char)(m_imDrawColor[2] * 255),
					(unsigned char)(m_imDrawColor[3] * 255)
				};


				m_drawingTool->ChangeColor(rayColor, m_drawColorDiffernece);
				m_drawingTool->Draw(gridPos);
			}
			else
			{
				m_drawingTool->Erase(gridPos);
			}
		}
	}

	currentGridUpdateTime += GetFrameTime();
	if (currentGridUpdateTime >= gridUpdateTime)
	{
		currentGridUpdateTime = 0.0f;
		m_grid->Update();
	}

	m_grid->Render();

	m_grid->SetPosition(m_gridPosX, m_gridPosY);
	m_grid->SetCellSize(m_cellSize);
	FallingSand::Element::m_size = m_cellSize;
	m_grid->Debug(m_gridDebug);

	Color rayColor;
	rayColor = {
		(unsigned char)(m_gridDebugColor[0] * 255),
		(unsigned char)(m_gridDebugColor[1] * 255),
		(unsigned char)(m_gridDebugColor[2] * 255),
		(unsigned char)(m_gridDebugColor[3] * 255)
	};
	m_grid->SetDebugColor(rayColor);


	for (int i = 0; i < dataSize - 1; ++i) {
		frameTimes[i] = frameTimes[i + 1];
	}
	frameTimes[dataSize - 1] = GetFrameTime() * 1000.0f; // Convert to milliseconds
}

void EditorScene::OnImGuiRender()
{
	if (ImGui::Begin("Grid"))
	{
		ImGui::InputFloat("Position X", &m_gridPosX, 1);
		ImGui::InputFloat("Position Y", &m_gridPosY, 1);
		ImGui::Spacing();
		ImGui::InputInt("Cell Size", &m_cellSize, 1);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Checkbox("Debug", &m_gridDebug);
		ImGui::Spacing();
		ImGui::ColorPicker4("Debug Color", m_gridDebugColor);
	} ImGui::End();

	if (ImGui::Begin("Preformace")) {
		std::string fps = ("FPS: " + std::to_string(GetFPS()));
		ImGui::Text(fps.c_str());
		ImGui::Spacing();
		ImGui::PlotLines("Frame Time (ms)", frameTimes, dataSize, 0, NULL, 0.0f, 100.0f, ImVec2(0, 80));
		ImGui::Text(std::to_string(GetFrameTime() * 1000.0f).c_str());
	}ImGui::End();

	if (ImGui::Begin("Drawing")) {
		ImGui::Checkbox("Draw", &m_draw);
		ImGui::Spacing();
		// Element
		int currentItemElement = static_cast<int>(m_drawElement); // Cast enum to int for Combo
		if (ImGui::Combo("Element", &currentItemElement, m_drawElementNames, IM_ARRAYSIZE(m_drawElementNames)))
		{
			m_drawElement = static_cast<FallingSand::DrawingTool::CurrentElement>(currentItemElement); // Update enum if selection changes
		}
		ImGui::Spacing();
		ImGui::Checkbox("Erase", &m_erase);
		ImGui::Spacing();
		// shape
		int currentItemShape = static_cast<int>(m_drawShape); // Cast enum to int for Combo
		if (ImGui::Combo("Shape", &currentItemShape, m_drawShapeNames, IM_ARRAYSIZE(m_drawShapeNames)))
		{
			m_drawShape = static_cast<FallingSand::DrawingTool::DrawShape>(currentItemShape); // Update enum if selection changes
		}
		ImGui::Spacing();
		ImGui::InputFloat("DrawSize", &m_drawSize, 1);
		ImGui::Spacing();
		ImGui::ColorPicker4("DrawColor", m_imDrawColor);
		ImGui::Spacing();
		ImGui::InputInt("ColorDifference", &m_drawColorDiffernece, 1);
	}ImGui::End();
}
