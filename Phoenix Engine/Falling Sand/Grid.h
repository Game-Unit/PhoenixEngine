#pragma once
#include "Element.h"
#include "raylib.h"

#include <random>
#include <vector>
#include <numeric>
#include <algorithm>

namespace FallingSand
{

	class Grid
	{
	public:
		Grid(float positionX, float positionY, int columns, int rows, float cellSize);
		~Grid();

		void Update();
		void Render();

		void SetPosition(float x, float y) { m_positionX = x; m_positionY = y; }
		void SetCellSize(float size) { m_cellSize = size; }
		void Debug(bool v) { m_debug = v; }
		void SetDebugColor(const Color& color) { m_debugColor = color; }

		void AddElement(Element* element);
		void ClearElement(int x, int y);
		Element* GetElement(int x, int y);

		Vector2 WorldToGrid(Vector2 pos);

		int GetColumns() { return m_columns; }
		int GetRows() { return m_rows; }

	private:
		std::vector<std::vector<Element*>> m_grid;

		float m_positionX;
		float m_positionY;
		int m_cellSize;

		int m_columns;
		int m_rows;

		std::random_device m_rd;
		std::mt19937 m_rng;
		std::vector<int> m_columnOrder;

		bool m_debug = false;
		Color m_debugColor = { 0, 255, 0, 255 };
	};

}