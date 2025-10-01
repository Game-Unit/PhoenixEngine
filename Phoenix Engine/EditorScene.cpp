#include "EditorScene.h"
#include "imgui.h"
#include "rlImGui.h"
#include "raylib.h"

EditorScene::EditorScene()
{
	m_cameraMovement = new CameraMovement();

	m_grid = new FallingSand::Grid(m_gridPosX, m_gridPosY, m_gridColumns, m_gridRows, m_cellSize);
}

void EditorScene::OnStart()
{
}

void EditorScene::OnUpdate()
{
	// Camera
	m_cameraMovement->Update();

	// Grid
	m_grid->Update();
	m_grid->SetPosition(m_gridPosX, m_gridPosY);
	m_grid->SetCellSize(m_cellSize);
	m_grid->Debug(m_gridDebug);

	Color rayColor;
	rayColor = {
		(unsigned char)(m_gridDebugColor[0] * 255),
		(unsigned char)(m_gridDebugColor[1] * 255),
		(unsigned char)(m_gridDebugColor[2] * 255),
		(unsigned char)(m_gridDebugColor[3] * 255)
	};
	m_grid->SetDebugColor(rayColor);
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
}
