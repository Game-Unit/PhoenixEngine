#include "DrawingTool.h"
#include "Element.h"
#include "Sand.h"
#include "Rock.h"
#include "../Core/Application.h"
#include "../Core/Math.h"

#define CAMERA Core::Application::m_camera

FallingSand::DrawingTool::DrawingTool(Grid* grid) : m_grid(grid)
{

}

void FallingSand::DrawingTool::Draw(Vector2 gridPos)
{    
    // Loop over an area based on DrawSize
    for (int y = -m_drawSize; y <= m_drawSize; y++)
    {
        for (int x = -m_drawSize; x <= m_drawSize; x++)
        {
            // Compute target position
            int gx = (int)gridPos.x + x;
            int gy = (int)gridPos.y + y;

            // Skip out-of-bounds cells
            if (gx < 0 || gx >= m_grid->GetColumns() || gy < 0 || gy >= m_grid->GetRows())
                continue;

            // Circle shape: skip points outside radius
            if (m_drawShape == DrawShape::circel)
            {
                float dist = sqrtf(x * x + y * y);
                if (dist > m_drawSize)
                    continue;
            }

            // Create element
            FallingSand::Element* element = nullptr;

            switch (m_currentElemnt)
            {
            case FallingSand::DrawingTool::CurrentElement::Sand:
            {
                element = new FallingSand::Sand(gx, gy, m_grid);

                Color color = {
                    (unsigned char)(Core::Math::Clamp(m_color.r + Core::Random::Range(-m_colorDifference, m_colorDifference), 0.0f, 255.0f)),
                    (unsigned char)(Core::Math::Clamp(m_color.g + Core::Random::Range(-m_colorDifference, m_colorDifference), 0.0f, 255.0f)),
                    (unsigned char)(Core::Math::Clamp(m_color.b + Core::Random::Range(-m_colorDifference, m_colorDifference), 0.0f, 255.0f)),
                    (unsigned char)(m_color.a)
                };

                element->SetColor(color);
                break;
            }
            case FallingSand::DrawingTool::CurrentElement::Rock:
            {
                element = new FallingSand::Rock(gx, gy, m_grid);

                Color color = {
                    (unsigned char)(Core::Math::Clamp(m_color.r + Core::Random::Range(-m_colorDifference, m_colorDifference), 0.0f, 255.0f)),
                    (unsigned char)(Core::Math::Clamp(m_color.g + Core::Random::Range(-m_colorDifference, m_colorDifference), 0.0f, 255.0f)),
                    (unsigned char)(Core::Math::Clamp(m_color.b + Core::Random::Range(-m_colorDifference, m_colorDifference), 0.0f, 255.0f)),
                    (unsigned char)(m_color.a)
                };

                element->SetColor(color);
                break;
            }
            default:
                break;
            }


            // Add to grid
            if (element != nullptr)
                m_grid->AddElement(element);
        }
    }
}

void FallingSand::DrawingTool::Erase(Vector2 gridPos)
{
    // Loop over an area based on DrawSize
    for (int y = -m_drawSize; y <= m_drawSize; y++)
    {
        for (int x = -m_drawSize; x <= m_drawSize; x++)
        {
            // Compute target position
            int gx = (int)gridPos.x + x;
            int gy = (int)gridPos.y + y;

            // Skip out-of-bounds cells
            if (gx < 0 || gx >= m_grid->GetColumns() || gy < 0 || gy >= m_grid->GetRows())
                continue;

            // Circle shape: skip points outside radius
            if (m_drawShape == DrawShape::circel)
            {
                float dist = sqrtf(x * x + y * y);
                if (dist > m_drawSize)
                    continue;
            }

            m_grid->ClearElement(gx, gy);
        }
    }
}

void FallingSand::DrawingTool::Update()
{
    if (m_drawShape == DrawShape::circel)
        DrawCircleLinesV(GetScreenToWorld2D(GetMousePosition(), CAMERA), m_drawSize * FallingSand::Element::m_size, RED);
    else
    {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), CAMERA);
        DrawRectangleLines(mousePos.x - m_drawSize * FallingSand::Element::m_size, mousePos.y - m_drawSize * FallingSand::Element::m_size, m_drawSize * FallingSand::Element::m_size * 2, m_drawSize * FallingSand::Element::m_size * 2, RED);
    }
}


void FallingSand::DrawingTool::ChangeElement(CurrentElement element)
{
	m_currentElemnt = element;
}

void FallingSand::DrawingTool::ChangeShape(DrawShape shape)
{
	m_drawShape = shape;
}

void FallingSand::DrawingTool::SetDrawSize(float size)
{
    m_drawSize = size;
}
