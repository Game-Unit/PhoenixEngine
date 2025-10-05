#pragma once

#include "Element.h"
#include "Grid.h"
#include "raylib.h"

namespace FallingSand
{

	class DrawingTool
	{
	public:
		DrawingTool(Grid* grid);

		void Draw(Vector2 gridPos);
		void Erase(Vector2 gridPos);
		void Update();

		FallingSand::Grid* m_grid;

		enum DrawShape
		{
			circel,
			box
		};
		DrawShape m_drawShape;

		enum CurrentElement
		{
			Sand,
			Rock
		};
		CurrentElement m_currentElemnt;

		void ChangeElement(CurrentElement element);
		void ChangeShape(DrawShape shape);
		void SetDrawSize(float size);
		void ChangeColor(Color color, int colorDiffrence) { m_color = color; m_colorDifference = colorDiffrence; }

	private:
		Color m_color = BLACK;
		int m_colorDifference = 0;
		float m_drawSize = 5;
	};
}