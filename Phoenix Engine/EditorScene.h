#pragma once

#include "Core/Scene.h"
#include "CameraMovement.h"
#include "Falling Sand/Grid.h"
#include "Falling Sand/Solid.h"
#include "Falling Sand/DrawingTool.h"

class EditorScene : public Core::Scene
{
public:
	EditorScene();
	~EditorScene();

	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;

private:
	CameraMovement* m_cameraMovement;
	FallingSand::DrawingTool* m_drawingTool;

	// gird
	FallingSand::Grid* m_grid;
	float m_gridPosX;
	float m_gridPosY;
	int m_gridColumns = 100;
	int m_gridRows = 100;
	int m_cellSize = 5;
	bool m_gridDebug = false;
	float m_gridDebugColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	float gridUpdateTime = 0.01f;
	float currentGridUpdateTime = 0.0f;

	// preformance Debug
	const int dataSize = 100;
	float frameTimes[100] = { 0 };
	int frameCount = 0;

	// drawing
	bool m_draw = true;

	FallingSand::DrawingTool::DrawShape m_drawShape;
	const char* m_drawShapeNames[2] = { "Circle", "Box" };
	bool m_erase = false;

	float m_drawSize = 5;

	FallingSand::DrawingTool::CurrentElement m_drawElement;
	const char* m_drawElementNames[2] = { "Sand", "Rock" };

	float m_imDrawColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	int m_drawColorDiffernece;
};

