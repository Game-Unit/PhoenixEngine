#pragma once

#include "Core/Scene.h"

class EditorScene : public Core::Scene
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
};

