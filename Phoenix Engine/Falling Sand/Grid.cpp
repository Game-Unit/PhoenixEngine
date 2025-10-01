#include "Grid.h"
#include "raylib.h"


FallingSand::Grid::Grid(float positionX, float positionY, int columns, int rows, float cellSize) 
	: m_positionX(positionX),  m_PositionY(positionY), m_columns(columns), m_rows(rows), m_cellSize(cellSize), m_columnOrder(columns), m_rng(m_rd())
{
	std::iota(m_columnOrder.begin(), m_columnOrder.end(), 0);
}

void FallingSand::Grid::Update()
{
	std::shuffle(m_columnOrder.begin(), m_columnOrder.end(), m_rng);

	std::vector<Element> grid(m_columns * m_rows);
	std::vector<bool> updated(m_columns * m_rows, false);

	for (int xi = 0; xi < m_columns; xi++)
	{
		int x = m_columnOrder[xi];
		for (int y = m_rows - 1; y >= 0; --y)
		{
			if (m_debug)
				DrawRectangleLines(m_positionX + x * m_cellSize, m_PositionY + y * m_cellSize, m_cellSize, m_cellSize, m_debugColor);
		}
	}
}

FallingSand::Grid::~Grid()
{
	
}
