#pragma once

#include "raylib.h"

namespace FallingSand { class Grid; }

namespace FallingSand
{

	class Element
	{
	public:
		Element(int x, int y, Grid* grid) : m_positionX(x), m_positionY(y), m_grid(grid) {}
		virtual void Update() = 0;

		void Render()
		{
			DrawRectangle(m_positionX * m_size, m_positionY * m_size, m_size, m_size, m_color);
		}

		void SetColor(Color color)
		{
			m_color = color;
		}

		void Awake()
		{
			m_asleep = false;
			m_sleepCount = 3;
		}

		int m_positionX;
		int m_positionY;
		static int m_size;

	protected:
		Color m_color{BLACK};

		Grid* m_grid;

		bool m_asleep = false;
		int m_sleepCount = 3;
	};
}