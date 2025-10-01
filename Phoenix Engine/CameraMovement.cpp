#include "CameraMovement.h"
#include "Core/Application.h"

#define CAMERA Core::Application::m_camera

void CameraMovement::Update()
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = Vector2Subtract(lastMouse, mouse);
        CAMERA.target = Vector2Add(CAMERA.target, Vector2Scale(delta, 1.0f / CAMERA.zoom));
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        float zoomIncrement = 0.1f;
        float newZoom = CAMERA.zoom + wheel * zoomIncrement;
        if (newZoom < 0.1f) newZoom = 0.1f; // Limit zoom in
        if (newZoom > 10.0f) newZoom = 10.0f; // Limit zoom out

        // Zoom towards mouse position
        Vector2 worldPos = GetScreenToWorld2D(mouse, CAMERA);
        CAMERA.zoom = newZoom;
        Vector2 newWorldPos = GetScreenToWorld2D(mouse, CAMERA);
        CAMERA.target = Vector2Add(CAMERA.target, Vector2Subtract(worldPos, newWorldPos));
    }

    lastMouse = mouse;
}
