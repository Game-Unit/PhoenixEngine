#pragma once

#include "Core/Scene.h"
#include "CameraMovement.h"
#include "Falling Sand/Grid.h"

class EditorScene : public Core::Scene
{
public:
	EditorScene();

	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;

private:
	CameraMovement* m_cameraMovement;

	// gird
	FallingSand::Grid* m_grid;
	float m_gridPosX;
	float m_gridPosY;
	int m_gridColumns = 200;
	int m_gridRows = 50;
	int m_cellSize = 5;
	bool m_gridDebug = false;
	float m_gridDebugColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
};

