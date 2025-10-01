#pragma once

#include "Core/Scene.h"

class GameScene : public Core::Scene
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
};