#pragma once

#include "raylib.h"
#include "raymath.h"

class CameraMovement
{
public:
	void Update();

private:
	Vector2 lastMouse = { 0 };
};

